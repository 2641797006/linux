import java.util.Scanner;

public class xx1{
	public static void main(String[] args)/* throws java.io.IOException*/{
		int i, n;
		double side, x, y, cx[], cy[];

		Scanner scan = new Scanner(System.in);
		println("请输入多边形边数, 边长, 中心点坐标:");
		n = scan.nextInt();
		side = scan.nextDouble();
		x = scan.nextDouble();
		y = scan.nextDouble();

		var rp = new RegularPolygon(n, side, x, y);

		cx = rp.getXPoints();
		cy = rp.getYPoints();

		printf("%d边形, 边长:%.2f, 中心(%.2f, %.2f)\n", n, side, x, y);
		printf("面积=%.2f\n", rp.area());
		printf("周长=%.2f\n", rp.perimeter());
		println("顶点坐标:");
		for (i=0; i<n; ++i)
			printf("(%.2f, %.2f)\n", cx[i], cy[i]);
	}

	private static void print(String s) {System.out.print(s);}
	private static void println(String s) {System.out.println(s);}
	private static void printf(String fmt, Object... args) {System.out.printf(fmt, args);}
}
