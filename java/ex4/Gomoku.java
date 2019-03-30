import javafx.scene.paint.Paint;
import javafx.scene.paint.Color;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;

public class Gomoku
{
	Canvas canvas;

	// 绘图起点
	double startX, startY;

	// 棋盘左上角坐标
	double chessboard_startX, chessboard_startY;
	// 棋盘行列格线数
	int chessboard_row, chessboard_col;
	// 棋盘格子宽高
	double grid_width, grid_height;
	// 棋盘格线paint
	Paint chessboard_paint;
	// 棋盘填充paint
	Paint chessboard_fill_paint;

	// 棋子椭圆横轴,纵轴
	double chessman_HAxis, chessman_VAxis;
	// 棋子填充paint
	Paint chessman_paint0;
	Paint chessman_paint1;

	// 外边距,内边距
	double margin, padding;
	Paint border_paint;

	public Gomoku()
	{
		canvas = new Canvas();

		startX = 0;
		startY = 0;
		margin = 10;
		padding = 10;
		setChessboardSize ( 19, 25.0 );
		setCanvasSize();

		chessboard_paint = Color.BLACK;
		chessboard_fill_paint = Color.WHITE;
		chessman_paint0 = Color.BLACK;
		chessman_paint1 = Color.WHITE;
		border_paint = Color.PINK;
	}

	public Canvas getCanvas()
	{
//		setCanvasSize();
		return this.canvas;
	}

	GraphicsContext	getGC()
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

	public Gomoku setStartXY (double x, double y)
	{
		startX = x;
		startY = y;
		setChessboardStartXY();
		return this;
	}

	public Gomoku setMargin (double margin)
	{
		this.margin = margin;
		setChessboardStartXY();
		return this;
	}

	public Gomoku setPadding (double padding)
	{
		this.padding = padding;
		setChessboardStartXY();
		return this;
	}

	public Gomoku setChessboardSize (int row_col, double grid_side)
	{
		return setChessboardSize (row_col, row_col, grid_side, grid_side);
	}

	public Gomoku setChessboardSize (int row, int col, double grid_width, double grid_height)
	{
		this.chessboard_row = row;
		this.chessboard_col = col;
		this.grid_width = grid_width;
		this.grid_height = grid_height;
		this.chessman_HAxis = grid_width;
		this.chessman_VAxis = grid_height;
		setChessboardStartXY();
		return this;
	}

	Gomoku setChessboardStartXY()
	{
		this.chessboard_startX = this.startX + this.margin + this.padding + this.grid_width/2.0;
		this.chessboard_startY = this.startY + this.margin + this.padding + this.grid_height/2.0;
		return this;
	}

	public Gomoku setCanvasSize ()
	{
		this.canvas.setWidth (this.chessboard_startX + this.grid_width*(this.chessboard_col-1) +
					this.grid_width/2.0 + this.padding + this.margin);
		this.canvas.setHeight (this.chessboard_startY + this.grid_height*(this.chessboard_row-1) +
					this.grid_height/2.0 + this.padding + this.margin);
		return this;
	}

/*---------- draw ----------*/

	public Gomoku draw()
	{
		return draw ( getGC() );
	}

	public Gomoku draw(GraphicsContext gc)
	{
		setCanvasSize();
		gc.setFill(Color.WHITE);
		gc.fillRect( startX, startY, getWidth(), getHeight() );
		gc.setFill(border_paint);
		gc.fillRoundRect( startX+margin, startY+margin,
				getWidth() - margin*2, getHeight() - margin*2,
				padding, padding);
		gc.setFill(Color.WHITE);
//		gc.fillRoundRect( startX+margin+padding, startY+margin+padding,
//				getWidth()-margin-padding, getHeight()-margin-padding,
//				grid_width/2.0, grid_height/2.0 );
		chessboard();

		setChessman(3, 6, 1);
		setChessman(4, 6, 0);
		setChessman(7, 3, 1);
		return this;
	}

	public void setChessman (int row, int col, int flag)
	{
		setChessman (row, col, flag==0 ? Color.BLUE : Color.RED);
	}

	public void setChessman (int row, int col, Paint paint)
	{
		setChessman (getGC(), row, col, paint);
	}

	public void setChessman (GraphicsContext gc, int row, int col, Paint paint)
	{
		setChessman ( gc,
			row, col, paint, chessman_HAxis, chessman_VAxis,
			this.chessboard_startX, this.chessboard_startY,
			this.grid_width, this.grid_height );
	}

	public static void setChessman (GraphicsContext gc,
				int row, int col, Paint paint, double HAxis, double VAxis,
				double x0, double y0, double width, double height)
	{
		double x, y;
		x = x0 + row * width - HAxis/2.0;
		y = y0 + col * height - VAxis/2.0;
		gc.setFill( paint );
		gc.fillOval( x, y, HAxis, VAxis );
	}

	void chessboard ()
	{
		chessboard ( getGC() );
	}

	public void chessboard (GraphicsContext gc)
	{
		chessboard ( gc, this.chessboard_paint,
			this.chessboard_startX, this.chessboard_startY,
			this.chessboard_row, this.chessboard_col,
			this.grid_width, this.grid_height );
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
