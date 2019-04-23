import java.lang.StringBuilder;

public class t3{
	public static void main(String[] args) throws Exception {
		int i;
		StringBuilder s=new StringBuilder("please sit spot. sit spot, sit spot here now here");
		println(""+s);
		do {
			i = 0;
			i += front(s);
			i += back(s);
			println(""+s);
		} while (i>0);
	}

	static int front(StringBuilder s) {
		int a, n=0, pos;
		String w;
		for (pos=0; pos<s.length(); ++pos) {
			pos = s.indexOf(",", pos);
			if (pos < 0)
				return n;
			pos = nextAlpha(s, pos+1);
			if (pos < 0)
				return n;
			w = word(s, pos);
			a = frontAdd(s, w, pos);
			n += a;
			pos += a;
		}
		return n;
	}

	static int back(StringBuilder s) {
		int n=0, pos, p;
		String w;
		for (pos=0; pos<s.length(); ++pos) {
			pos = s.indexOf(",", pos);
			if (pos < 0)
				return n;
			p = lastAlpha(s, pos-1);
			if (p < 0)
				return n;
			w = word(s, p);
			p = backAdd(s, w, pos);
			pos += p;
			n += p;
		}
		return n;
	}

	static int backAdd(StringBuilder s, String w, int pos) {
		int i, p, n=0;
		for (p=0; p<s.length(); ) {
			p = s.indexOf(w, p);
			if (p < 0)
				return n;
			p += w.length();
			for (i=p; i<s.length()-1; ++i)
				if ( ! ctype.isspace(s.charAt(i)))
					break;
			if (ctype.isalpha(s.charAt(i))) {
				s.insert(p, ',');
				if (p <= pos) {
					++n;
					++pos;
				}
				++p;
			}
		}
		return n;
	}

	static int frontAdd(StringBuilder s, String w, int pos) {
		int i, p, n=0;
		for (p=0; p<s.length(); p+=w.length()) {
			p = s.indexOf(w, p);
			if (p < 0)
				return n;
//			if (p>0 && ctype.isalpha(s.charAt(p-1)) || p+w.length()<s.length() && ctype.isalpha(s.charAt(p+w.length())))
//				continue;
			for (i=p-1; i>0; --i)
				if ( ! ctype.isspace(s.charAt(i)))
					break;
			if (i<p-1 && ctype.isalpha(s.charAt(i))) {
				s.insert(i+1, ',');
				++p;
				if (i+1 <= pos) {
					++n;
					++pos;
				}
			}
		}
		return n;
	}

	static String word(StringBuilder s, int pos) {
		int i;
		for (i=pos; i<s.length(); ++i)
			if ( ! ctype.isalpha(s.charAt(i)))
				break;
		return s.substring(pos, i);
	}

	static int nextAlpha(StringBuilder s, int pos) {
		int i;
		for (i=pos; i<s.length()-1; ++i)
			if ( ! ctype.isspace(s.charAt(i)))
				break;
		return ctype.isalpha(s.charAt(i)) ? i : -1;
	}

	static int lastAlpha(StringBuilder s, int pos) {
		int i;
		for (i=pos; i>0; --i)
			if ( ! ctype.isspace(s.charAt(i)))
				break;
		if ( ! ctype.isalpha(s.charAt(i)))
			return -1;
		for (; i>0; --i)
			if ( ! ctype.isalpha(s.charAt(i)))
				break;
		return ctype.isalpha(s.charAt(i)) ? i : i+1;
	}

	static void print(String s) {System.out.print(s);}
	static void println(String s) {System.out.println(s);}
	static void printf(String fmt, Object... args) {System.out.printf(fmt, args);}
}
