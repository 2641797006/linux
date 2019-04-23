import java.lang.StringBuilder;

public class t3{
	public static void main(String[] args) throws Exception {
t3 c= new t3();
		StringBuilder s=new StringBuilder("please sit spot. sit spot, sit spot here now here");
		println(""+s);
		c.front(s);
		println(""+s);
	}

	int front(StringBuilder s) {
		int n=0, pos;
		String w;
		for (pos=0; pos<s.length(); ++pos) {
			pos = s.indexOf(",", pos);
			if (pos < 0)
				return n;
println("find , "+pos);
			pos = nextAlpha(s, pos+1);
			if (pos < 0)
				return n;
			w = word(s, pos);
println("word:"+w);
			pos += frontAdd(s, w, pos);
++n;
if(n>20) return n;
		}
		return n;
	}

	static int frontAdd(StringBuilder s, String w, int pos) {
		int i, p, n=0;
		for (p=0; p<s.length(); p+=w.length()) {
			p = s.indexOf(w, p);
			if (p < 0)
				return n;
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
			if (ctype.isspace(s.charAt(i)))
				break;
		if ( ! ctype.isalpha(s.charAt(i)))
			return -1;
		for (; i>0; --i)
			if (ctype.isalpha(s.charAt(i)))
				continue;
		return ctype.isalpha(s.charAt(i)) ? i : i-1;
	}

	static void print(String s) {System.out.print(s);}
	static void println(String s) {System.out.println(s);}
	static void printf(String fmt, Object... args) {System.out.printf(fmt, args);}
}
