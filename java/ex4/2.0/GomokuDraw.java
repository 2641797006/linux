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

	// 内边距, 边框宽度, 外边距
	double padding, borderWidth, margin;
	// 边框填充颜色
	Paint borderFill;
	// 外边填充颜色
	Paint marginFill;

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
/*
public:
	GomokuDraw();

	GomokuDraw clear();

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

	GomokuDraw setChessman (int row, int col, boolean flag); // false = B, true = W
	GomokuDraw setChessman (int row, int col, Paint stroke, Paint fill);
	GomokuDraw setChessman (GraphicsContext gc, int row, int col, Paint stroke, Paint fill);
	static void setChessman (GraphicsContext gc,
				int row, int col, Paint stroke, Paint fill, double HAxis, double VAxis,
				double x0, double y0, double width, double height);

	GomokuDraw chessboard ();
	GomokuDraw chessboard (GraphicsContext);
	static void chessboard (GraphicsContext gc, Paint paint,
					double x0, double y0, int row, int col, double width, double height);

	GomokuDraw clear(GraphicsContext gc, Paint paint);
	GomokuDraw fillBorder (GraphicsContext gc, Paint paint)
	GomokuDraw fillChessboard (GraphicsContext gc, Paint paint)

private:
	GomokuDraw flushXY();
*/
	public GomokuDraw()
	{
		canvas = new Canvas();

		setStartXY(0,0);
		setMargin(10);
		setPadding(10);
		setBorderFill ( Color.WHITE );

		setChessmanStroke ( Color.BLACK, Color.WHITE );
		setChessmanFill ( Color.BLACK, Color.WHITE );

		setChessboardStroke ( Color.BLACK );
		setChessboardFill ( Color.WHITE );
		setChessboardSize ( 19, 25.0 );

		flushCanvasSize();

		draw();
	}

	public GomokuDraw draw()
	{
		return draw ( getGC() );
	}

	public GomokuDraw draw(GraphicsContext gc)
	{
		clear();

		setBorderFill( Color.web("#FFBCD1") );
		fillBorder();

		setChessboardStroke ( Color.BLACK );
		setChessboardFill ( Color.web("#AAF9F8") );
		fillChessboard();

		chessboard();

		setChessmanStroke(Color.PINK, Color.PINK);
		setChessmanFill(Color.BLACK, Color.WHITE);

		return this;
	}

/* ------------------------------------------------ */

	public GomokuDraw setGC (GraphicsContext gc)
	{
		this.gc = gc;
		return this;
	}

	public GomokuDraw setStartXY (double cx, double cy)
	{
		startX = cx;
		startY = cy;
		flushXY();
		return this;
	}

	public GomokuDraw setPadding (double padding)
	{
		this.padding = padding;
		flushXY();
		return this;
	}

	public GomokuDraw setBorderWidth (double width)
	{
		this.borderWidth = width;
		flushXY();
		return this;
	}

	public GomokuDraw setMargin (double margin)
	{
		this.margin = margin;
		flushXY();
		return this;
	}

	public GomokuDraw setBorderFill (Paint paint)
	{
		this.borderFill = paint;
		return this;
	}

	public GomokuDraw setMarginFill (Paint paint)
	{
		this.marginFill = paint;
		return this;
	}

/* -------棋盘--------- */

	public GomokuDraw setChessboardRank (int rank)
	{
		this.chessboardRank = rank;
		flushXY();
		return this;
	}

	public GomokuDraw setGridSide (double side)
	{
		this.gridSide = side;
		flushXY();
		return this;
	}

	public GomokuDraw setChessboardStroke (Paint paint)
	{
		this.chessboardStroke = paint;
		return this;
	}

	public GomokuDraw setChessboardFill (Paint paint)
	{
		this.chessboardFill = paint;
		return this;
	}

/* -------棋子--------- */

	public GomokuDraw setChessmanSide (double side)
	{
		this.chessmanSide = side;
		return this;
	}

	public GomokuDraw setChessmanStroke (Paint B, Paint W)
	{
		this.chessmanStrokeB = B;
		this.chessmanStrokeW = W;
		return this;
	}

	public GomokuDraw setChessmanFill (Paint B, Paint W)
	{
		this.chessmanFillB = B;
		this.chessmanFillW = W;
		return this;
	}

/* ------------------------- */

	GomokuDraw flushXY ()
	{
		this.chessboardStartX = this.startX + this.margin + this.borderWidth + this.padding;
		this.chessboardStartY = this.startY + this.margin + this.borderWidth + this.padding;
		this.chessboardEndX = this.chessboardStartX + this.gridSide * (this.chessboardRank - 1);
		this.chessboardEndY = this.chessboardStartY + this.gridSide * (this.chessboardRank - 1);
		this.endX = this.chessboardEndX + this.margin + this.borderWidth + this.padding;
		this.endY = this.chessboardEndY + this.margin + this.borderWidth + this.padding;
		return this;
	}

	GomokuDraw clear ()
	{
		gc.setFill( this.marginFill );
		gc.fillRect( startX, startY, endX - startX, endY - startY );
		return this;
	}

	public GomokuDraw fillBorder (GraphicsContext gc, Paint paint)
	{ // then fill chessboard
		gc.setFill(paint);
		gc.fillRoundRect( startX + margin, startY + margin,
					getWidth() - margin*2, getHeight() - margin*2,
					borderWidth, borderWidth);
		return this;
	}

	GomokuDraw fillChessboard ()
	{
		return fillChessboard ( getGC(), chessboardFill );
	}

	public GomokuDraw fillChessboard (GraphicsContext gc, Paint paint)
	{ // the stroke is used to fill blank line
		gc.setFill(paint);
		gc.fillRoundRect( this.chessboardStartX - this.gridSide/2.0, this.chessboardStartY - this.gridSide/2.0,
					this.gridSide * this.chessboardRank, this.gridSide * this.chessboardRank,
					this.gridSide/2.0, this.gridSide/2.0 );
		gc.setStroke(paint);
		gc.strokeRoundRect( this.chessboardStartX - this.gridSide/2.0, this.chessboardStartY - this.gridSide/2.0,
					this.gridSide * this.chessboardRank, this.gridSide * this.chessboardRank,
					this.gridSide/2.0, this.gridSide/2.0 );
		return this;
	}

	public GomokuDraw setChessman (int row, int col, boolean flag)
	{
		return setChessman (row, col,
				flag ? chessmanStrokeW : chessmanStrokeB,
				flag ? chessmanFillW : chessmanFillB);
	}

	public GomokuDraw setChessman (int row, int col, Paint stroke, Paint fill)
	{
		return setChessman (getGC(), row, col, stroke, fill);
	}

	public GomokuDraw setChessman (GraphicsContext gc, int row, int col, Paint stroke, Paint fill)
	{
		setChessman ( gc,
			row, col, stroke, fill, chessmanSide, chessmanSide,
			this.chessboardStartX, this.chessboardStartY,
			this.gridSide, this.gridSide );
		return this;
	}

	public static void setChessman (GraphicsContext gc,
				int row, int col, Paint stroke, Paint fill, double HAxis, double VAxis,
				double x0, double y0, double width, double height)
	{
		double x, y;
		x = x0 + col * width - HAxis/2.0;
		y = y0 + row * height - VAxis/2.0;
		if (stroke != null) {
			gc.setStroke( stroke );
			gc.strokeOval( x, y, HAxis, VAxis );
		}
		if (fill != null ) {
			gc.setFill( fill );
			gc.fillOval( x, y, HAxis, VAxis );
		}
	}

	GomokuDraw chessboard ()
	{
		return chessboard ( getGC() );
	}

	public GomokuDraw chessboard (GraphicsContext gc)
	{
		chessboard ( gc, this.chessboardStroke,
			this.chessboardStartX, this.chessboardStartY,
			this.chessboardRank, this.chessboardRank,
			this.gridSide, this.gridSide );
		return this;
	}

	public static void chessboard (GraphicsContext gc, Paint paint,
					double x0, double y0, int row, int col, double width, double height)
	{ // 左上角坐标, 行列格线数, 格子宽高
		int i;
		double x1, y1;

		x1 = x0 + width * (col - 1);
		y1 = y0 + height * (row - 1);

		gc.setStroke( paint );

		for (i=0; i<row; ++i)
			gc.strokeLine(x0, y0+height*i, x1, y0+height*i);
		for (i=0; i<col; ++i)
			gc.strokeLine(x0+width*i, y0, x0+width*i, y1);
	}
}
