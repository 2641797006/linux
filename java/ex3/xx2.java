import java.util.Scanner;
import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.shape.Polygon;
import javafx.stage.Stage;
import javafx.scene.paint.Color;

public class xx2 extends Application /* throws java.io.IOException*/{
	public void start(Stage stage) {
		int i, n;
		double side, x, y, cx[], cy[];

		Scanner scan = new Scanner(System.in);
		println("请输入多边形边数, 边长, 中心点坐标:");
		n = scan.nextInt();
		side = scan.nextDouble();
		x = scan.nextDouble();
		y = scan.nextDouble();

		var rp = new RegularPolygon_X(n, side, x, y);

		rp.setAngleFix(-1);

		cx = rp.getXPoints();
		cy = rp.getYPoints();

		printf("%d边形, 边长:%.2f, 中心(%.2f, %.2f)\n", n, side, x, y);
		printf("面积=%.2f\n", rp.area());
		printf("周长=%.2f\n", rp.perimeter());
		println("顶点坐标:");
		for (i=0; i<n; ++i)
			printf("(%.2f, %.2f)\n", cx[i], cy[i]);

		Group root = new Group();
		Scene scene = new Scene(root, side*n, side*n*0.618, RGB(0x2095f3));
		stage.setScene(scene);

		Polygon polygon = new Polygon();
		polygon.setStroke(RGB(0xffc107));
		polygon.getPoints().addAll(merge_xy(cx, cy, n));
		polygon.setFill(RGB(0xffc107));

		root.getChildren().add(polygon);
		stage.show();
	}

	public static Double[] merge_xy(double cx[], double cy[], int n) {
		int i;
		Double xy[] = new Double[n<<1];
		for (i=0; i<n; ++i) {
			xy[i<<1] = cx[i];
			xy[(i<<1)+1] = cy[i];
		}
		return xy;
	}

	public static Color RGB(int rgb) {
		return RGBx(rgb, 1);
	}

	public static Color RGBx(int rgb, double opacity) {
		final double q = 0xff;
		return new Color((rgb>>16)/q, (rgb>>8 & 0xff)/q, (rgb & 0xff)/q, opacity);
	}

	private static void print(String s) {System.out.print(s);}
	private static void println(String s) {System.out.println(s);}
	private static void printf(String fmt, Object... args) {System.out.printf(fmt, args);}
}
