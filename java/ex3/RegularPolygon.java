import java.lang.Math;

public class  RegularPolygon{
	private int n; //边数
	private double side; //边长
	private double x; //中心横坐标
	private double y; //中心纵坐标
	private double cx[]; //顶点横坐标
	private double cy[]; //顶点纵坐标
	private double _area;
//	private double _perimeter;

	private int flags; //记录数据是否发生改变
	private final int fs_size = 	0x07;
	private final int fs_area =	0x01;
//	private final int fs_perimeter= 0x02;
	private final int fs_xy = 	0x10;
	private final int fs_points = 	0x14;
	private final int fs_all = 	0xff;

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
		flags = fs_all;
	}

	public int getN() { return n; }
	public double getSide() { return side; }
	public double getX() { return x; }
	public double getY() { return y; }

	public void setN(int _n) { n = _n; flags |= fs_size; }
	public void setSide(double _side) { side = _side; flags |= fs_size; }
	public void setX(double _x) { x = _x; flags |= fs_xy; }
	public void setY(double _y) { y = _y; flags |= fs_xy; }

	public double area() {
		if ((flags&fs_area) != 0) {
			flags &= ~fs_area;
			return _area = n*side*side/4.0/Math.tan(Math.PI/n);
		}
		return _area;
	}

	public double perimeter() {
		return n*side;
	}

	public double[] getXPoints() {
		flush_xy();
		return cx;
	}

	public double[] getYPoints() {
		flush_xy();
		return cy;
	}

	private void flush_xy() {
		if ((flags&fs_points) != 0) {
			flags &= ~fs_points;
			calculate_points_xy();
		}
	}

	private void calculate_points_xy() { //计算各个顶点坐标
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

