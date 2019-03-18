public class bigint_test{
	public static void main(String[] args){
		int i;
		BigInt b, pow, sum;
		b = new BigInt();
		pow = new BigInt(2);
		sum = new BigInt(1);
		for (i=1; i<=100; ++i) {
			sum.mul(b.assign(pow).add(1));
			pow.mul(2);
		}
		println(""+sum.toString());
	}

	private static void print(String s) {System.out.print(s);}
	private static void println(String s) {System.out.println(s);}
	private static void printf(String fmt, Object... args) {System.out.printf(fmt, args);}
}
