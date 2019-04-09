import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;

public class xx1 extends Application
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
