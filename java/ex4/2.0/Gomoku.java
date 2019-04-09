import java.lang.Math;

import javafx.scene.layout.Pane;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Paint;
import javafx.scene.paint.Color;
import javafx.scene.control.Button;

import javafx.event.EventHandler;
import javafx.event.ActionEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.MouseDragEvent;

import javafx.scene.layout.VBox;
import javafx.geometry.Pos;

import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;

public class Gomoku {
	// 镶板
	Pane pane;
	// 界面坐标
	double startX, startY;
	double endX, endY;
	// 画布
	Canvas canvas;
	// Gomoku绘图类
	GomokuDraw gdraw;
	// 棋盘上的棋子

	byte[][] CM;
	// 当前棋子颜色
	boolean flag;
	// 五子成龙 dragon默认为5
	int dragon;
	// 有效点击范围
	double clickRange;

	// 操作界面
	Paint oiFill;
	double oiStartX, oiStartY;
	double oiEndX, oiEndY;

	// 游戏计数
	int round;

	public Gomoku()
	{
		this.pane = new Pane();
		this.canvas = new Canvas();
		this.gdraw = new GomokuDraw(this.canvas.getGraphicsContext2D());
		this.CM = new byte[gdraw.getChessboardRank()+2][gdraw.getChessboardRank()+2];
		this.flag = false;
		setDragon(5);
		setClickRange(gdraw.getGridSide() * 3.9/10.0);
		this.oiFill = Color.web("#E3F7FE");
		this.round = 0;

		this.startX = gdraw.getStartX();
		this.startY = gdraw.getStartY();
		this.oiStartX = gdraw.getEndX();
		this.oiStartY = this.startY;
		this.oiEndX = this.oiStartX + gdraw.getWidth() * 0.618;
		this.oiEndY = gdraw.getEndY();
		this.endX = this.oiEndX;
		this.endY = this.oiEndY;

		this.canvas.setOnMouseClicked(new EventHandler<MouseEvent>() {
			public void handle(MouseEvent event) {
				mouseEvent(event);
			}
		});
		this.canvas.setWidth(this.endX - this.startX);
		this.canvas.setHeight(this.endY - this.startY);

		gdraw.draw();
		gdraw.getGC().setFill(this.oiFill);
		gdraw.getGC().fillRect(this.oiStartX, this.oiStartY, this.oiEndX-this.oiStartX, this.oiEndY-this.oiStartY);
		flushCurrentPlayer();

		VBox vbox = new VBox(30);
		vbox.setLayoutX(this.oiStartX);
		vbox.setLayoutY(this.oiStartY);
		vbox.setMinWidth(VBox.USE_PREF_SIZE);
		vbox.setMaxWidth(VBox.USE_PREF_SIZE);
		vbox.setPrefWidth(this.oiEndX - this.oiStartX);
		vbox.setMinHeight(VBox.USE_PREF_SIZE);
		vbox.setMaxHeight(VBox.USE_PREF_SIZE);
		vbox.setPrefHeight(this.oiEndY - this.oiStartY);

		vbox.setAlignment(Pos.CENTER);
		vbox.getChildren().add(resetButton("重新开始", 100, 100));

		this.pane.getChildren().add(this.canvas);
		this.pane.getChildren().add(vbox);
	}

	public Pane getPane() { return this.pane; }
	public double getWidth() { return this.endX - this.startX; }
	public double getHeight() { return this.endY - this.startY; }

	public int getDragon() { return this.dragon; }
	public double getClickRange() { return this.clickRange; }

	public Gomoku setDragon(int n) {
		this.dragon = n;
		return this;
	}

	public Gomoku setClickRange(double d)
	{
		this.clickRange = d;
		return this;
	}

	public Gomoku flushCurrentPlayer() {
		double cx = this.oiStartX + (this.oiEndX-this.oiStartX)/2.0;
		double cy = this.oiStartY + 75;
		double width = this.oiEndX - this.oiStartX - 30;
		double height = 36;
		if (this.round == 0) {
			gdraw.getGC().setFill(gdraw.getChessboardFill());
			gdraw.getGC().fillRoundRect(cx - width/2.0, cy - height/2.0, width, height, height/2.0, height/2.0);
		}
		gdraw.drawChessman( cx, cy, this.flag);
		return this;
	}

	public Button resetButton(String text, double cx, double cy)
	{
		Button button = new Button();

		button.setText( text );
		button.setLayoutX( cx + this.oiStartX );
		button.setLayoutY( cy + this.oiStartY );
		button.setOnAction( new EventHandler<ActionEvent>(){
			public void handle(ActionEvent event)
			{
				reset();
			}
		} );
		return button;
	}

	public Gomoku reset() {
		this.gdraw.draw();
		this.flag = false;
		flushCurrentPlayer();
		this.CM = new byte[gdraw.getChessboardRank()+2][gdraw.getChessboardRank()+2];
		return this;
	}

	boolean win(int row, int col)
	{
		if (stat(row, col, 1, 0, 0) >= dragon) {
			stat(row, col, 1, 0, 1);
			return true;
		}
		if (stat(row, col, 0, 1, 0) >= dragon) {
			stat(row, col, 0, 1, 1);
			return true;
		}
		if (stat(row, col, 1, 1, 0) >= dragon) {
			stat(row, col, 1, 1, 1);
			return true;
		}
		if (stat(row, col, 1, -1, 0) >= dragon) {
			stat(row, col, 1, -1, 1);
			return true;
		}
		return false;
	}

	int stat(int row, int col, int ra, int ca, int doWhat)
	{
		++row;
		++col;
		int r, c, n=1;
		byte key = CM[row][col];

		if (doWhat == 1)
			drawWinChessman(row-1, col-1);
		r = row + ra;
		c = col + ca;
		while ( CM[r][c] == key ) {
			if (doWhat == 0)
				++n;
			else
				drawWinChessman(r-1, c-1);
			r += ra;
			c += ca;
		}
		r = row - ra;
		c = col - ca;
		while ( CM[r][c] == key ) {
			if (doWhat == 0)
				++n;
			else
				drawWinChessman(r-1, c-1);
			r -= ra;
			c -= ca;
		}
		return n;
	}

	Gomoku drawWinChessman(int row, int col)
	{
		gdraw.drawChessman(row, col, gdraw.getChessmanSide()*1.2, Color.PINK, Color.GOLD);
		double d = this.flag ? 0 : 1;
		gdraw.drawChessman(row, col, gdraw.getChessmanSide(), Color.PINK, Color.color(d, d, d, 0.666));
		return this;
	}

/*----- handle -----*/

	public void mouseEvent(MouseEvent event)
	{
		int c[]=click(event.getX(), event.getY());
		if ( c == null || CM [c[0]+1] [c[1]+1] != 0 )
			return;
		this.gdraw.drawChessman(c[0], c[1], flag);
		if ( this.flag ) {
			CM [c[0]+1] [c[1]+1] = 1;
			this.flag = false;
		} else {
			CM [c[0]+1] [c[1]+1] = -1;
			this.flag = true;
		}
		++this.round;
		flushCurrentPlayer();
		if ( win(c[0], c[1]) ) {
			Alert alert = new Alert(AlertType.INFORMATION);
			alert.setTitle("Game Over!");
			alert.setHeaderText(null);
			alert.setContentText( (this.flag ? "Black" : "White") + " Player Win !" );
			alert.showAndWait();
			reset();
		}
	}

	int[] click(double cx, double cy)
	{
		int row, col;
		if (cx < this.gdraw.getChessboardStartX()-getClickRange() || cx > this.gdraw.getChessboardEndX()+getClickRange())
			return null;
		if (cy < this.gdraw.getChessboardStartY()-getClickRange() || cy > this.gdraw.getChessboardEndY()+getClickRange())
			return null;
		cx -= this.gdraw.getChessboardStartX();
		cy -= this.gdraw.getChessboardStartY();
		row = (int) ( cy / this.gdraw.getGridSide() );
		col = (int) ( cx / this.gdraw.getGridSide() );
		if ( cx % this.gdraw.getGridSide() > this.gdraw.getGridSide() - getClickRange() )
			++col;
		else if ( cx % this.gdraw.getGridSide() > getClickRange() )
			return null;
		if ( cy % this.gdraw.getGridSide() > this.gdraw.getGridSide() - getClickRange() )
			++row;
		else if ( cy % this.gdraw.getGridSide() > getClickRange() )
			return null;
		if ( Math.pow(cx - col*this.gdraw.getGridSide(), 2) + Math.pow(cy - row*this.gdraw.getGridSide(), 2)
				> Math.pow(getClickRange(), 2) )
			return null;
		return new int[]{row, col};
	}
}
