
import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.paint.Paint;
import javafx.scene.paint.Color;
import javafx.scene.layout.Pane;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;

public class xx2 extends Application {
	public void start(Stage stage) {
		Gomoku gomoku = new Gomoku();

		//Scene scene = new Scene(pane, 1000, 618);
		Pane pane = new Pane();
		pane.getChildren().add(gomoku.getCanvas());
		Scene scene = new Scene(pane, 1000, 618);

		stage.setScene(scene);
		stage.setTitle("setTitle this");
		stage.show();
	}


}

class Gomoku {
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
	// 棋子椭圆横轴,纵轴
	double chessman_HAxis, chessman_VAxis;
	// 棋子填充paint
	Paint chessman_paint0;
	Paint chessman_paint1;
	// 边框距离
	double border;

	public Gomoku()
	{
		startX = 0;
		startY = 0;
		draw();
	}

	public Canvas getCanvas()
	{
		return this.canvas;
	}

	GraphicsContext	getGC()
	{
		return this.canvas.getGraphicsContext2D();
	}

	Gomoku setStartXY (double x, double y)
	{
		startX = x;
		startY = y;
		return this;
	}

	Gomoku setChessboardSize (int row_col, double grid_side)
	{
		return setChessboardSize (row_col, row_col, grid_side, grid_side);
	}

	Gomoku setChessboardSize (int row, int col, double grid_width, double grid_height)
	{
		this.chessboard_row = row;
		this.chessboard_col = col;
		this.grid_width = grid_width;
		this.grid_height = grid_height;
		this.chessman_long_axis = grid_width;
		this.chessman_short_axis = grid_height;
		return this;
	}

	public void draw()
	{
		border = 20;
		chessboard_startX = border;
		chessboard_startY = border;
		setChessboardSize(19, 25.0);

		double cw, ch;
		cw = chessboard_startX + grid_width * (chessboard_col - 1) + border;
		ch = chessboard_startY + grid_height * (chessboard_row - 1) + border;
		canvas = new Canvas(cw, ch);
//		gc = canvas.getGraphicsContext2D();
//		gc.clearRect(0,0, canvas.getWidth(), canvas.getHeight());
//		gc.setFill(Color.PINK);
//		gc.fillRoundRect( 0, 0, cw, ch, border, border );
//		gc.setFill(Color.WHITE);
//		gc.fillRect( x0, y0, cw-border*2, ch-border*2);
		chessboard();

		setChessman(3, 6, 1);
		setChessman(4, 6, 0);
		setChessman(7, 3, 1);
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
			row, col, paint, chessman_radius,
			this.chessboard_startX, this.chessboard_startY,
			this.grid_width, this.grid_height );
	}

	public static void setChessman (GraphicsContext gc,
				int row, int col, Paint paint, double radius,
				double x0, double y0, double width, double height)
	{
		double x, y;
		x = x0 + row * width - radius;
		y = y0 + col * height - radius;
		gc.setFill( paint );
		gc.fillOval( x, y, radius*2, radius*2 );
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
