import javafx.scene.paint.Paint;
import javafx.scene.paint.Color;
import javafx.scene.canvas.GraphicsContext;

public class GomokuDraw
{
	// 图形上下文
	GraphicsContext gc;
	// 绘图起点坐标
	double startX, startY;
	// 绘图终点坐标
	double endX, endY;

	// 外边距, 边框宽度, 内边距
	double margin, borderWidth, padding;
	// 外边填充颜色
	Paint marginFill;
	// 边框填充颜色
	Paint borderFill;

// 棋盘
	// 棋盘左上角坐标
	double chessboardStartX, chessboardStartY;
	// 棋盘右下角坐标
	double chessboardEndX, chessboardEndY;
	// 棋盘行列格线数(default=19)
	int chessboardRank;
	// 棋盘格子边长
	double gridSide;
	// 棋盘格线颜色
	Paint chessboardStroke;
	// 棋盘填充颜色
	Paint chessboardFill;

// 棋子
	// 棋子直径
	double chessmanSide;
	// 棋子边线颜色
	Paint chessmanStrokeB;
	Paint chessmanStrokeW;
	// 棋子填充颜色
	Paint chessmanFillB;
	Paint chessmanFillW;

// 星位
	// 星位直径
	double starSide;
	// 星位边线颜色
	Paint starStroke;
	// 星位填充颜色
	Paint starFill;
/*
public:
	GomokuDraw();

	GomokuDraw fillMargin();

	GomokuDraw setStartXY (double x, double y);
	GomokuDraw setMargin (double);
	GomokuDraw setPadding (double);
	GomokuDraw setBorderFill (Paint);

	GomokuDraw setChessmanStroke (Paint B, Paint W);
	GomokuDraw setChessmanFill (Paint B, Paint W);

	GomokuDraw setChessboardStroke (Paint);
	GomokuDraw setChessboardFill (Paint);
	GomokuDraw setChessboardSize (int row_col, double grid_side);
	GomokuDraw setChessboardSize (int row, int col, double gridSide, double gridSide);

	GomokuDraw drawChessman (int row, int col, boolean flag); // false = B, true = W
	GomokuDraw drawChessman (int row, int col, Paint stroke, Paint fill);
	GomokuDraw drawChessman (GraphicsContext gc, int row, int col, Paint stroke, Paint fill);
	static void drawChessman (GraphicsContext gc,
				int row, int col, Paint stroke, Paint fill, double HAxis, double VAxis,
				double x0, double y0, double width, double height);

	GomokuDraw drawChessboard ();

	GomokuDraw fillMargin(GraphicsContext gc, Paint paint);
	GomokuDraw fillBorder (GraphicsContext gc, Paint paint)
	GomokuDraw fillChessboard (GraphicsContext gc, Paint paint)

private:
	GomokuDraw flushXY();
*/
	public GomokuDraw(GraphicsContext gc)
	{
		this.gc = gc;
		this.startX = 0;
		this.startY = 0;

		this.margin = 10;
		this.borderWidth = 10;
		setMarginFill(Color.web("#f0f0f2"));
		setBorderFill(Color.web("#ffbcd1"));

		this.chessboardRank = 19;
		this.gridSide = 25;
		setPadding(getGridSide()/2.0); // padding = gridSide/2.0
		setChessboardStroke(Color.BLACK);
		setChessboardFill(Color.web("#aaf9f8"));

		setChessmanSide(getGridSide()-1);
		setChessmanStrokeB(Color.PINK);
		setChessmanStrokeW(Color.PINK);
		setChessmanFillB(Color.BLACK);
		setChessmanFillW(Color.WHITE);

		setStarSide(getGridSide() * 3.6/10.0);
		setStarStroke(null);
		setStarFill(Color.web("#888a85"));
	}

	public GomokuDraw draw()
	{
		fillMargin();
		fillBorder();
		fillChessboard();
		fillChessboard();

		drawChessboard();
		drawStar();
		return this;
	}
	// draw star in 19*19
	public GomokuDraw drawStar() {
		drawStar( 3, 3);
		drawStar( 9, 3);
		drawStar(15, 3);
		drawStar( 3, 9);
		drawStar( 9, 9);
		drawStar(15, 9);
		drawStar( 3, 15);
		drawStar( 9, 15);
		drawStar(15, 15);
		return this;
	}

/* ------------------------------------------------ */

	public GraphicsContext getGC() { return this.gc; }
	public double getStartX() { return this.startX; }
	public double getStartY() { return this.startY; }

	public double getMargin() { return this.margin; }
	public double getBorderWidth() { return this.borderWidth; }
	public double getPadding() { return this.padding; }
	public Paint getMarginFill() { return this.marginFill; }
	public Paint getBorderFill() { return this.borderFill; }

	public GomokuDraw setGC(GraphicsContext gc) {
		this.gc = gc;
		return this;
	}

	public GomokuDraw setStartX(double cx) {
		startX = cx;
		flushXY();
		return this;
	}

	public GomokuDraw setStartY(double cy) {
		startY = cy;
		flushXY();
		return this;
	}

	public GomokuDraw setMargin(double margin) {
		this.margin = margin;
		flushXY();
		return this;
	}

	public GomokuDraw setBorderWidth(double width) {
		this.borderWidth = width;
		flushXY();
		return this;
	}

	public GomokuDraw setPadding(double padding) {
		this.padding = padding;
		flushXY();
		return this;
	}

	public GomokuDraw setBorderFill(Paint paint) {
		this.borderFill = paint;
		return this;
	}

	public GomokuDraw setMarginFill(Paint paint) {
		this.marginFill = paint;
		return this;
	}

/* -------棋盘--------- */

	public int getChessboardRank() { return this.chessboardRank; }
	public double getGridSide() { return this.gridSide; }
	public Paint getChessboardStroke() { return this.chessboardStroke; }
	public Paint getChessboardFill() { return this.chessboardFill; }

	public GomokuDraw setChessboardRank(int rank) {
		this.chessboardRank = rank;
		flushXY();
		return this;
	}

	public GomokuDraw setGridSide(double side) {
		this.gridSide = side;
		flushXY();
		return this;
	}

	public GomokuDraw setChessboardStroke(Paint paint) {
		this.chessboardStroke = paint;
		return this;
	}

	public GomokuDraw setChessboardFill(Paint paint) {
		this.chessboardFill = paint;
		return this;
	}

/* -------棋子--------- */

	public double getChessmanSide() { return this.chessmanSide; }
	public Paint getChessmanStrokeB() { return this.chessmanStrokeB; }
	public Paint getChessmanStrokeW() { return this.chessmanStrokeW; }
	public Paint getChessmanFillB() { return this.chessmanFillB; }
	public Paint getChessmanFillW() { return this.chessmanFillW; }

	public GomokuDraw setChessmanSide(double side) {
		this.chessmanSide = side;
		return this;
	}

	public GomokuDraw setChessmanStrokeB(Paint paint) {
		this.chessmanStrokeB = paint;
		return this;
	}

	public GomokuDraw setChessmanStrokeW(Paint paint) {
		this.chessmanStrokeW = paint;
		return this;
	}

	public GomokuDraw setChessmanFillB(Paint paint) {
		this.chessmanFillB = paint;
		return this;
	}

	public GomokuDraw setChessmanFillW(Paint paint) {
		this.chessmanFillW = paint;
		return this;
	}

/* -------星位--------- */

	public double getStarSide() { return this.starSide; }
	public Paint getStarStroke() { return this.starStroke; }
	public Paint getStarFill() { return this.starFill; }

	public GomokuDraw setStarSide(double side) {
		this.starSide = side;
		return this;
	}

	public GomokuDraw setStarStroke(Paint paint) {
		this.starStroke = paint;
		return this;
	}

	public GomokuDraw setStarFill(Paint paint) {
		this.starFill = paint;
		return this;
	}

/* -----------flush, fill-------------- */

	GomokuDraw flushXY() {
		this.chessboardStartX = this.startX + this.margin + this.borderWidth + this.padding;
		this.chessboardStartY = this.startY + this.margin + this.borderWidth + this.padding;
		this.chessboardEndX = this.chessboardStartX + this.gridSide * (this.chessboardRank - 1);
		this.chessboardEndY = this.chessboardStartY + this.gridSide * (this.chessboardRank - 1);
		this.endX = this.chessboardEndX + this.margin + this.borderWidth + this.padding;
		this.endY = this.chessboardEndY + this.margin + this.borderWidth + this.padding;
		return this;
	}

	GomokuDraw fillMargin() {
		gc.setFill( this.marginFill );
		gc.fillRect( startX, startY, endX - startX, endY - startY );
		return this;
	}

	GomokuDraw fillBorder() {
		gc.setFill( this.borderFill );
		gc.fillRoundRect( startX + margin, startY + margin,
					endX - startX - margin*2, endY - startY - margin*2,
					borderWidth, borderWidth);
		return this;
	}

	GomokuDraw fillChessboard() {
		gc.setFill( this.chessboardFill );
		gc.fillRoundRect( this.chessboardStartX - this.padding, this.chessboardStartY - this.padding,
					this.gridSide * (this.chessboardRank - 1) + this.padding*2,
					this.gridSide * (this.chessboardRank - 1) + this.padding*2,
					this.padding, this.padding );
		gc.setStroke( this.chessboardFill );
		gc.strokeRoundRect( this.chessboardStartX - this.padding, this.chessboardStartY - this.padding,
					this.gridSide * (this.chessboardRank - 1) + this.padding*2,
					this.gridSide * (this.chessboardRank - 1) + this.padding*2,
					this.padding, this.padding );
		return this;
	}

/* --------- draw ----------- */

	public GomokuDraw drawStar(int row, int col) {
		return drawChessman(row, col, this.starSide, this.starStroke, this.starFill);
	}

	public GomokuDraw drawChessman(int row, int col, boolean flag) {
		return drawChessman(row, col, this.chessmanSide,
					flag ? this.chessmanStrokeW : this.chessmanStrokeB,
					flag ? this.chessmanFillW : this.chessmanFillB);
	}

	public GomokuDraw drawChessman(double cx, double cy, boolean flag) {
		return drawChessman(cx, cy, this.chessmanSide,
					flag ? this.chessmanStrokeW : this.chessmanStrokeB,
					flag ? this.chessmanFillW : this.chessmanFillB);
	}

	GomokuDraw drawChessman(int row, int col, double side, Paint stroke, Paint fill) {
		double cx = this.chessboardStartX + col * this.gridSide - side/2.0;
		double cy = this.chessboardStartY + row * this.gridSide - side/2.0;
		return drawChessman( cx, cy, side, stroke, fill );
	}

	GomokuDraw drawChessman(double cx, double cy, double side, Paint stroke, Paint fill) {
		if (stroke != null) {
			this.gc.setStroke( stroke );
			this.gc.strokeOval( cx, cy, side, side );
		}
		if (fill != null ) {
			this.gc.setFill( fill );
			this.gc.fillOval( cx, cy, side, side );
		}
		return this;
	}

	GomokuDraw drawChessboard() {
		int i;
		gc.setStroke( this.chessboardStroke );
		for (i=0; i<this.chessboardRank; ++i)
			gc.strokeLine(this.chessboardStartX, this.chessboardStartY+this.gridSide*i,
					this.chessboardEndX, this.chessboardStartY+this.gridSide*i);
		for (i=0; i<this.chessboardRank; ++i)
			gc.strokeLine(this.chessboardStartX+this.gridSide*i, this.chessboardStartY,
					this.chessboardStartX+this.gridSide*i, this.chessboardEndY);
		return this;
	}
}
