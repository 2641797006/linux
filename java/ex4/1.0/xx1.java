
import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.layout.Pane;
import javafx.scene.control.Button;
import javafx.event.EventHandler;
import javafx.event.ActionEvent;

public class xx1 extends Application
{
	public void start(Stage stage)
	{
		double offsetX;
		Gomoku gomoku = new Gomoku();
		offsetX = gomoku.getWidth();

		Pane pane = new Pane();
		pane.getChildren().add(gomoku.getCanvas());

		Button button = new Button();
		button.setText("重新开始");
		button.setLayoutX(offsetX+20);
		button.setLayoutY(20);
		button.setOnAction( new EventHandler<ActionEvent>(){
			public void handle(ActionEvent event)
			{
				gomoku.reset();
			}
		} );
		pane.getChildren().add(button);

		Scene scene = new Scene(pane, gomoku.getWidth()*1.618, gomoku.getHeight());

		stage.setScene(scene);
		stage.setTitle("Gomoku");
		stage.setResizable(false);

		stage.show();
	}
}
