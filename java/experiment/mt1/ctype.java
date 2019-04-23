public final class ctype{
	public static boolean isdigit(int c) {
		return '0' <= c && c <= '9' ? true : false;
	}

	public static boolean islower(int c) {
		return 'a' <= c && c <= 'z' ? true : false;
	}

	public static boolean isupper(int c) {
		return 'A' <= c && c <= 'Z' ? true : false;
	}

	public static boolean isalpha(int c) {
		return islower(c) || isupper(c);
	}

	public static boolean isalnum(int c) {
		return isalpha(c) || isdigit(c);
	}

	public static boolean isxdigit(int c) {
		return isdigit(c) || 'a'<=c && c<='f' || 'A'<=c && c<='F';
	}

	public static boolean isspace(int c) {
		return c==' ' || c=='\n' || c=='\r' || c=='\t';
	}

	public static boolean isblank(int c) {
		return c==' ' || c=='\t';
	}

}
