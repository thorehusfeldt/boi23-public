import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.TreeMap;
import java.util.TreeSet;

public class JoklSimpleSegComp {
	static int cap;
	static long[] seg;
	static long max = Long.MAX_VALUE / 5;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] line = br.readLine().split(" ");
		long b = Long.parseLong(line[0]);
		long m = Long.parseLong(line[1]);
		int d = Integer.parseInt(line[2]);
		int n = Integer.parseInt(line[3]) + 1;
		
		long[] a = new long[n];
		long[] dp = new long[n];
		TreeSet<Long> a_mod_m = new TreeSet<>();
		a_mod_m.add(0l);
		for(int i = 1; i<n; i++){
			a[i] = Long.parseLong(br.readLine());
			a_mod_m.add(a[i] % m);
		}
		// Elegant? Maybe not. Map each value x from a_mod_m to the number of elements y in a_mod_m such that y < x
		Long[] tmp = new Long[0];
		Long[] a_mod_m_arr = a_mod_m.toArray(tmp);
		TreeMap<Long, Integer> a_mod_m_map = new TreeMap<>(); 
		for(int i = 0; i<a_mod_m_arr.length; i++) {
			a_mod_m_map.put(a_mod_m_arr[i], i);
		}
		a_mod_m_map.put(m+2, a_mod_m_arr.length); // To ensure each element has a ceiling
		
		build(n);
		upd(0, 0);
		for(int i = 1; i<n; i++) {
			int p = comp(a[i] % m, a_mod_m_map);
			long x = a[i]/m*(d+m);
			dp[i] = x + Math.min(qry(0, p-1)+d+m, qry(p, n-1)) - d;
			upd(p, dp[i] - x);
		}
		long ans = max;
		for(int i = 0; i<n; i++) {
			long dist = b-a[i];
			long total = dp[i] + dist + d * ((dist+m-1)/m - 1);
			ans = Math.min(ans, total);
		}
		
		System.out.println(ans);
	}
	
	static void build(int m) {
		for(cap = 1; cap < m; cap *= 2);
		seg = new long[2*cap];
		for(int i =0; i<2*cap; i++) {
			seg[i] = max;
		}
	}
	
	static void upd(int i, long v) {
		i += cap;
		seg[i] = v;
		for(i /= 2; i >= 1; i /= 2) {
			seg[i] = Math.min(seg[2*i], seg[2*i+1]);
		}
	}
	
	static long qry(int l, int r) {
		return qry(l, r, 0, cap-1, 1);
	}
	static long qry(int l, int r, int a, int b, int i) {
		if(l <= a && b <= r)
			return seg[i];
		if(b < l || r < a)
			return max;
		int m = (a+b)/2;
		return Math.min(qry(l, r, a, m, 2*i), qry(l, r, m+1, b, 2*i+1));
	}
	
	// Gets the number of elements in set that are strictly less than x
	static int comp(long x, TreeMap<Long, Integer> map) {
		return map.ceilingEntry(x).getValue();
	}
}
