import java.io.Console;

public class t2{
	public static void main(String[] args) throws Exception {
		Console cons = System.console();
		String pwd;
		char[] ca = cons.readPassword("请输入密码: ");
		pwd = new String(ca);
		println(pwd);
		if (Check.scheck(pwd))
			println("Valid Password");
		else
			println("Invalid Password");
	}

	static void print(String s) {System.out.print(s);}
	static void println(String s) {System.out.println(s);}
	static void printf(String fmt, Object... args) {System.out.printf(fmt, args);}
}
