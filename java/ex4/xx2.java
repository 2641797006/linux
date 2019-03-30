
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

	// 棋盘左上角坐标
	double chessboard_x0, chessboard_y0;
	// 棋盘行列格线数
	int chessboard_row, chessboard_col;
	// 棋盘格子宽高
	double grid_width, grid_height;
	// 棋盘格线paint
	Paint chessboard_paint;
	// 棋子半径
	double chessman_radius;
	// 棋子填充paint
	Paint chessman_paint0;
	Paint chessman_paint1;
	// 边框距离
	double border;

	public Gomoku() {
		draw();
	}

	public Canvas getCanvas() {
		return this.canvas;
	}

	GraphicsContext	getGC() {
		return this.canvas.getGraphicsContext2D();
	}

	public void draw()
	{
		border = 20;
		chessboard_x0 = border;
		chessboard_y0 = border;
		chessboard_row = 19;
		chessboard_col = 19;
		grid_width = 25;
		grid_height = 25;
		chessman_radius = 12;

		double cw, ch;
		cw = chessboard_x0 + grid_width * (chessboard_col - 1) + border;
		ch = chessboard_y0 + grid_height * (chessboard_row - 1) + border;
		canvas = new Canvas(cw, ch);
//		gc = canvas.getGraphicsContext2D();
//		gc.clearRect(0,0, canvas.getWidth(), canvas.getHeight());
//		gc.setFill(Color.PINK);
//		gc.fillRoundRect( 0, 0, cw, ch, border, border );
//		gc.setFill(Color.WHITE);
//		gc.fillRect( x0, y0, cw-border*2, ch-border*2);
		chessboard();

		setChessman(3, 6, Color.RED);
		setChessman(4, 6, Color.PINK);
		setChessman(7, 3, Color.BLUE);
	}

	public void setChessman (int row, int col, Paint paint)
	{
		setChessman (getGC(), row, col, paint);
	}

	public void setChessman (GraphicsContext gc, int row, int col, Paint paint)
	{
		setChessman ( gc,
			row, col, paint, chessman_radius,
			this.chessboard_x0, this.chessboard_y0,
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
			this.chessboard_x0, this.chessboard_y0,
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
