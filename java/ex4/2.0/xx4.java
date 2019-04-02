
import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.layout.Pane;
import javafx.scene.control.Button;
import javafx.event.EventHandler;
import javafx.event.ActionEvent;
import javafx.scene.canvas.Canvas;

public class xx4 extends Application
{
	public void start(Stage stage)
	{
		Gomoku gomoku = new Gomoku();

		Scene scene = new Scene(gomoku.getPane(), gomoku.getWidth(), gomoku.getHeight());

		stage.setScene(scene);
		stage.setTitle("Gomoku");
		stage.setResizable(false);

		stage.show();
	}
}
