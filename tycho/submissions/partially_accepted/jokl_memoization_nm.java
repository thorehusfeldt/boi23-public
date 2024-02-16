// @EXPECTED_GRADES@ RTE AC AC RTE AC RTE RTE
//
// RTEs can also be TLEs, depending on where the code runs (out
// of heap space or out of time)

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class jokl_memoization_nm{
	static long[] caves;
	static long z, c;
	static int m, n;

	// Let memo[i][k] be the minimum cost of reaching z
	// starting in caves[i] at a time t = k mod m
	static long[][] memo;
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] line = br.readLine().split(" ");
		z = Long.parseLong(line[0]);
		m = Integer.parseInt(line[1]);
		c = Long.parseLong(line[2]);
		n = Integer.parseInt(line[3]) + 1;

		memo = new long[n][m];
		caves = new long[n];
		// Implicitly let pos. 0 be a cave
		for(int i = 1; i<n; i++) {
			caves[i] = Long.parseLong(br.readLine());
		}
		
		for(int i = n-1; i>= 0; i--) {
			for(int j = m-1; j >= 0; j--) {
				explore(j, i);
			}
		}
		
		System.out.println(explore(0, 0));
	}
	
	// Return damage suffered when traveling from caves[cave]
	// either taking off at time `time` (go-solution)
	// or waiting for next pulse (wait-solution)
	static long explore(int time, int cave) {
		if(memo[cave][time % m] != 0)
			return memo[cave][time % m];

		if(cave == (n-1)) {
			long go = damage(time, z-caves[cave]);
			int pulseTime = m * (time/m) + m;
			long wait = damage(pulseTime, z-caves[cave]) + (pulseTime-time);
			long sol = Math.min(go, wait);
			memo[cave][time % m] = sol;
			return sol;
		}
		long dist = caves[cave+1] - caves[cave];
		long go = damage(time, dist) + explore((int)(time+dist) % m, cave+1);
		int pulseTime = m * (time/m) + m;
		long wait = damage(pulseTime, dist) + (pulseTime-time) + explore((int)(pulseTime+dist) % m, cave+1);
		long sol = Math.min(go, wait);
		memo[cave][time % m] = sol;
		return sol;
	}
	
	// Damage received when traveling `dist` distance starting at time `time`,
	// assuming that final location is a cave
	static long damage(int time, long dist) {
		long pulses = (time+dist-1)/m - time/m;
		return c*pulses + dist;
	}
}
