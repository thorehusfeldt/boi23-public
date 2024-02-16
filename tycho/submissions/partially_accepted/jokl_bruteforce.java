// @EXPECTED_GRADES@ TLE AC TLE TLE TLE TLE TLE
import java.util.Scanner;

public class jokl_bruteforce {
	static int[] caves;
	static int z, m, c, n;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		z = sc.nextInt();
		m = sc.nextInt();
		c = sc.nextInt();
		n = sc.nextInt() + 1;
	
		caves = new int[n];
		// Implicitly let pos. 0 be a cave
		for(int i = 1; i<n; i++) {
			caves[i] = sc.nextInt();
		}
		
		System.out.println(explore(0, 0));
	}
	
	// Return damage suffered when traveling from caves[cave]
	// either taking off at time `time` (go-solution)
	// or waiting for next pulse (wait-solution)
	static int explore(int time, int cave) {
		if(cave == (n-1)) {
			int go = damage(time, z-caves[cave]);
			int pulseTime = m * (time/m) + m;
			int wait = damage(pulseTime, z-caves[cave]) + (pulseTime-time);
			return Math.min(go, wait);
		}
		int dist = caves[cave+1] - caves[cave];
		int go = damage(time, dist) + explore(time+dist, cave+1);
		int pulseTime = m * (time/m) + m;
		int wait = damage(pulseTime, dist) + (pulseTime-time) + explore(pulseTime+dist, cave+1);
		return Math.min(go, wait);
	}
	
	// Damage received when traveling `dist` distance starting at time `time`,
	// assuming that final location is a cave
	static int damage(int time, int dist) {
		int pulses = (time+dist-1)/m - time/m;
		return c*pulses + dist;
	}
}
