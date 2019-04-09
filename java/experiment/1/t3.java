import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import java.util.Optional;
import javafx.scene.control.TextInputDialog;
import java.util.Scanner;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;


public class t3 extends Application{
	public void start(Stage stage) {
		TextInputDialog input = new TextInputDialog();
		input.setTitle("TextInputDialog");
		input.setHeaderText("Enter two number");
		input.setContentText("2 number:");

		Optional<String> ins = input.showAndWait();
		String str = ins.toString();
		str = str.substring(9, str.length()-1);

		Scanner scan = new Scanner(str);
		double d1 = scan.nextDouble();
		double d2 = scan.nextDouble();
		double d3 = d1 + d2;

		Alert alert = new Alert(AlertType.INFORMATION);
		alert.setTitle("result");
		alert.setHeaderText("计算结果");
		alert.setContentText(""+d1+" + "+d2+" = "+d3);
		
		alert.showAndWait();
	//	Scene scane = new Scene(root, 800, 600);
	//	stage.setScene(scene);
	//	stage.show();
	}



}
