import javafx.scene.paint.Paint;
import javafx.scene.paint.Color;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;

public class GomokuDraw
{
protected
	Canvas canvas;

	// 绘图起点
protected
	double startX, startY;

	// 棋盘左上角坐标
protected
	double chessboard_startX, chessboard_startY;
	// 棋盘右下角坐标
protected
	double chessboard_endX, chessboard_endY;
	// 棋盘行列格线数
protected
	int chessboard_row, chessboard_col;
	// 棋盘格子宽高
protected
	double grid_width, grid_height;
	// 棋盘格线paint
protected
	Paint chessboard_stroke;
	// 棋盘填充paint
protected
	Paint chessboard_fill;

	// 棋子椭圆横轴,纵轴
protected
	double chessman_HAxis, chessman_VAxis;
	// 棋子边线paint
protected
	Paint chessmanB_stroke;
protected
	Paint chessmanW_stroke;
	// 棋子填充paint
protected
	Paint chessmanB_fill;
protected
	Paint chessmanW_fill;

	// 外边距,内边距
protected
	double margin, padding;
	// 边框填充paint
protected
	Paint border_fill;
/*
public:
	GomokuDraw();

	Canvas getCanvas();
	double getWidth();
	double getHeight();
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
	GomokuDraw setChessboardSize (int row, int col, double grid_width, double grid_height);

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
	GomokuDraw flushCanvasSize();
	GomokuDraw flushChessboardCoord();
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
	}

	public GomokuDraw draw()
	{
		return draw ( getGC() );
	}

	public GomokuDraw draw(GraphicsContext gc)
	{
		flushCanvasSize();

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

	public Canvas getCanvas()
	{
		return this.canvas;
	}

	public GraphicsContext getGC()
	{
		return this.canvas.getGraphicsContext2D();
	}

	public double getWidth()
	{
		return this.canvas.getWidth();
	}

	public double getHeight()
	{
		return this.canvas.getHeight();
	}

	public GomokuDraw setStartXY (double x, double y)
	{
		startX = x;
		startY = y;
		flushChessboardCoord();
		return this;
	}

	public GomokuDraw setMargin (double margin)
	{
		this.margin = margin;
		flushChessboardCoord();
		return this;
	}

	public GomokuDraw setPadding (double padding)
	{
		this.padding = padding;
		flushChessboardCoord();
		return this;
	}

	public GomokuDraw setBorderFill (Paint paint)
	{
		this.border_fill = paint;
		return this;
	}

	public GomokuDraw setChessmanStroke (Paint B, Paint W)
	{
		this.chessmanB_stroke = B;
		this.chessmanW_stroke = W;
		return this;
	}

	public GomokuDraw setChessmanFill (Paint B, Paint W)
	{
		this.chessmanB_fill = B;
		this.chessmanW_fill = W;
		return this;
	}

	public GomokuDraw setChessboardStroke (Paint paint)
	{
		this.chessboard_stroke = paint;
		return this;
	}

	public GomokuDraw setChessboardFill (Paint paint)
	{
		this.chessboard_fill = paint;
		return this;
	}

	public GomokuDraw setChessboardSize (int row_col, double grid_side)
	{
		return setChessboardSize (row_col, row_col, grid_side, grid_side);
	}

	public GomokuDraw setChessboardSize (int row, int col, double grid_width, double grid_height)
	{
		this.chessboard_row = row;
		this.chessboard_col = col;
		this.grid_width = grid_width;
		this.grid_height = grid_height;
		// 棋子大小 与 棋盘格子 相关
		this.chessman_HAxis = grid_width-1;
		this.chessman_VAxis = grid_height-1;

		flushChessboardCoord();
		return this;
	}

	GomokuDraw flushCanvasSize ()
	{
		this.canvas.setWidth (this.chessboard_endX + this.grid_width/2.0 + this.padding + this.margin);
		this.canvas.setHeight (this.chessboard_endY + this.grid_height/2.0 + this.padding + this.margin);
		return this;
	}

	GomokuDraw flushChessboardCoord()
	{
		this.chessboard_startX = this.startX + this.margin + this.padding + this.grid_width/2.0;
		this.chessboard_startY = this.startY + this.margin + this.padding + this.grid_height/2.0;
		this.chessboard_endX = this.chessboard_startX + this.grid_width * (this.chessboard_col - 1);
		this.chessboard_endY = this.chessboard_startY + this.grid_height * (this.chessboard_row - 1);
		return this;
	}

	public GomokuDraw clear()
	{
		return clear( getGC(), Color.WHITE );
	}

	public GomokuDraw clear(GraphicsContext gc, Paint paint)
	{
		gc.setFill(paint);
		gc.fillRect( startX, startY, getWidth(), getHeight() );
		return this;
	}

	GomokuDraw fillBorder ()
	{
		return fillBorder ( getGC(), border_fill );
	}

	public GomokuDraw fillBorder (GraphicsContext gc, Paint paint)
	{ // then fill chessboard
		gc.setFill(paint);
		gc.fillRoundRect( startX + margin, startY + margin,
					getWidth() - margin*2, getHeight() - margin*2,
					padding, padding);
		return this;
	}

	GomokuDraw fillChessboard ()
	{
		return fillChessboard ( getGC(), chessboard_fill );
	}

	public GomokuDraw fillChessboard (GraphicsContext gc, Paint paint)
	{ // the stroke is used to fill blank line
		gc.setFill(paint);
		gc.fillRoundRect( this.chessboard_startX - this.grid_width/2.0, this.chessboard_startY - this.grid_height/2.0,
					this.grid_width * this.chessboard_col, this.grid_height * this.chessboard_row,
					this.grid_width/2.0, this.grid_height/2.0 );
		gc.setStroke(paint);
		gc.strokeRoundRect( this.chessboard_startX - this.grid_width/2.0, this.chessboard_startY - this.grid_height/2.0,
					this.grid_width * this.chessboard_col, this.grid_height * this.chessboard_row,
					this.grid_width/2.0, this.grid_height/2.0 );
		return this;
	}

	public GomokuDraw setChessman (int row, int col, boolean flag)
	{
		return setChessman (row, col,
				flag ? chessmanW_stroke : chessmanB_stroke,
				flag ? chessmanW_fill : chessmanB_fill);
	}

	public GomokuDraw setChessman (int row, int col, Paint stroke, Paint fill)
	{
		return setChessman (getGC(), row, col, stroke, fill);
	}

	public GomokuDraw setChessman (GraphicsContext gc, int row, int col, Paint stroke, Paint fill)
	{
		setChessman ( gc,
			row, col, stroke, fill, chessman_HAxis, chessman_VAxis,
			this.chessboard_startX, this.chessboard_startY,
			this.grid_width, this.grid_height );
		return this;
	}

	public static void setChessman (GraphicsContext gc,
				int row, int col, Paint stroke, Paint fill, double HAxis, double VAxis,
				double x0, double y0, double width, double height)
	{
		double x, y;
		x = x0 + col * width - HAxis/2.0;
		y = y0 + row * height - VAxis/2.0;
		gc.setStroke( stroke );
		gc.strokeOval( x, y, HAxis, VAxis );
		gc.setFill( fill );
		gc.fillOval( x, y, HAxis, VAxis );
	}

	GomokuDraw chessboard ()
	{
		return chessboard ( getGC() );
	}

	public GomokuDraw chessboard (GraphicsContext gc)
	{
		chessboard ( gc, this.chessboard_stroke,
			this.chessboard_startX, this.chessboard_startY,
			this.chessboard_row, this.chessboard_col,
			this.grid_width, this.grid_height );
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
