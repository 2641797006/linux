
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.scene.paint.Color;
import javafx.scene.layout.Pane;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;

public class xx2 extends Application {
	public void start(Stage stage) {
		GomokuPane pane = new GomokuPane();

		//Scene scene = new Scene(pane, 1000, 618);
		Scene scene = new Scene(pane, pane.getWidth(), pane.getHeight());

		stage.setScene(scene);
		stage.setTitle("setTitle this");
		stage.show();
	}


}

class GomokuPane extends Pane {
	Canvas canvas;
	GraphicsContext gc;

	public GomokuPane() {
		draw();
		getChildren().add(canvas);
	}

	public void draw() {
		canvas = new Canvas(1000, 618);
		setWidth(1000);
		setHeight(618);
		gc = canvas.getGraphicsContext2D();
		gc.clearRect(0,0, canvas.getWidth(), canvas.getHeight());
		gc.setFill(Color.YELLOW);
		gc.fillPolygon(new double[]{0, 0, 100, 100}, new double[]{0, 100, 100, 0}, 4);

		gc.strokeRect(200,200,100,300);
		gc.fillRect(200,200,100,300);

		chessboard(100, 150, 19, 19, 20, 20);
	}

	void chessboard (double x0, double y0, int row, int col, double width, double height)
	{
		int i;
		double x1, y1;
		x1 = x0 + width * (col - 1);
		y1 = y0 + height * (row - 1);
		for (i=0; i<row; ++i)
			gc.strokeLine(x0, y0+height*i, x1, y0+height*i);
		for (i=0; i<col; ++i)
			gc.strokeLine(x0+width*i, y0, x0+width*i, y1);
	}

}
