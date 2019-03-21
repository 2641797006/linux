import java.lang.Math;

public class  RegularPolygon{
	private int n; //边数
	private double side; //边长
	private double x; //中心横坐标
	private double y; //中心纵坐标
	private double cx[]; //顶点横坐标
	private double cy[]; //顶点纵坐标

	public  RegularPolygon() {
		this(3, 1.0);
	}

	public  RegularPolygon(int _n) {
		this(_n, 1.0);
	}

	public  RegularPolygon(int _n, double _side) {
		this(_n, _side, _n*_side/5.0, _n*_side/5.0);
	}

	public  RegularPolygon(int _n, double _side, double _x, double _y) {
		n = _n;
		x = _x;
		y = _y;
		side = _side;
	}

	public int getN() { return n; }
	public double getSide() { return side; }
	public double getX() { return x; }
	public double getY() { return y; }

	public void setN(int _n) { n = _n; }
	public void setSide(double _side) { side = _side; }
	public void setX(double _x) { x = _x; }
	public void setY(double _y) { y = _y; }

	public double area() {
		return n*side*side/4.0/Math.tan(Math.PI/n);
	}

	public double perimeter() {
		return n*side;
	}

	public double[] getXPoints() {
		calculate_points_xy();
		return cx;
	}

	public double[] getYPoints() {
		calculate_points_xy();
		return cy;
	}

	private void calculate_points_xy() { //计算顶点坐标
		int i;
		double angle=0, top_angle=Math.PI*2.0/n, diagonal=side/2.0/Math.sin(top_angle/2.0);

		cx = new double[n];
		cy = new double[n];
		for (i=0; i<n; ++i) {
			cx[i] = zerofix( diagonal*Math.cos(angle)+x );
			cy[i] = zerofix( diagonal*Math.sin(angle)+y );
			angle += top_angle;
		}
	}

	private double zerofix(double x) { //很小的数将被调整为0
		return Math.abs(x)<1.0E-14 ? 0.0 : x;
	}
}

