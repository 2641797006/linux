public class Check{
	String regex;

	Check() { regex = "^[a-zA-Z0-9]{8,}$"; }

	public boolean check(String s) {
		return regexCheck(s) && otherCheck(s);
	}

	public static boolean scheck(String s) {
		return new Check().check(s);
	}

	boolean regexCheck(String s) {
		return s.matches(regex);
	}

	boolean otherCheck(String s) {
		int i, n=0, c;
		for (i=0; i<s.length(); ++i) {
			c = s.charAt(i);
			if ('0' <= c && c <= '9')
				++n;
		}
		return n>=3 ? true : false;
	}
}
