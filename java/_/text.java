import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import javafx.stage.Screen;

public class text extends Application {
	public void start(Stage stage) {
		stage.setTitle("日历");
		Group root = new Group();

		Text text = new Text();

		text.setText(__.calendarOfYear(2019, 4));
		text.setFill(__.RGB(0));

		root.getChildren().add(text);

		Font font = new Font(-1);
		printf("font-size=%f\n", font.getSize());
		Screen screen = Screen.getPrimary();
		printf("dpi=%f\n", screen.getDpi());

		Scene scene = new Scene(root, text.getLayoutBounds().getWidth(), text.getLayoutBounds().getHeight(), __.RGB(0xf0f0f2));

		stage.setScene(scene);
		stage.show();
	}

	private static void print(String s) {System.out.print(s);}
	private static void println(String s) {System.out.println(s);}
	private static void printf(String fmt, Object... args) {System.out.printf(fmt, args);}

}
