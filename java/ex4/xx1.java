
import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.layout.Pane;

import javafx.event.EventHandler;
import javafx.scene.input.MouseEvent;

public class xx1 extends Application {
	public void start(Stage stage) {
		Gomoku gomoku = new Gomoku();

		Pane pane = new Pane();

		gomoku.draw();

		pane.getChildren().add(gomoku.getCanvas());

		Scene scene = new Scene(pane, gomoku.getWidth(), gomoku.getHeight());

		stage.setScene(scene);
		stage.setTitle("setTitle this");
		stage.show();
		gomoku.setChessman(18, 18, true);
	}
}
