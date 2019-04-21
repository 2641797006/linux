import java.lang.Byte;
import java.lang.Short;
import java.lang.Integer;
import java.lang.Long;
import java.lang.Float;
import java.lang.Double;

public class t1{
	public static void main(String[] args) throws Exception {
		println("");
		println("byte   (" + Byte.MIN_VALUE + ", " + Byte.MAX_VALUE + ")");
		println("short  (" + Short.MIN_VALUE + ", " + Short.MAX_VALUE + ")");
		println("int    (" + Integer.MIN_VALUE + ", " + Integer.MAX_VALUE + ")");
		println("long   (" + Long.MIN_VALUE + ", " + Long.MAX_VALUE + ")");
		println("float  (" + Float.MIN_VALUE + ", " + Float.MAX_VALUE + ")");
		println("double (" + Double.MIN_VALUE + ", " + Double.MAX_VALUE + ")");
		println("");
	}

	static void print(String s) {System.out.print(s);}
	static void println(String s) {System.out.println(s);}
	static void printf(String fmt, Object... args) {System.out.printf(fmt, args);}
}
