import java.lang.Math;

import javafx.scene.layout.Pane;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Button;

import javafx.event.EventHandler;
import javafx.event.ActionEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.MouseDragEvent;

public class Gomoku {
	// 镶板
	Pane pane;
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
	// 界面坐标
	double startX, startY;
	double endX, endY;
	// 操作界面坐标
	double oiStartX, oiStartY;
	double oiEndX, oiEndY;

	public Gomoku()
	{
		this.pane = new Pane();
		this.canvas = new Canvas();
		this.gdraw = new GomokuDraw(this.canvas.getGraphicsContext2D());
		this.CM = new byte[gdraw.getChessboardRank()+2][gdraw.getChessboardRank()+2];
		this.flag = false;
		setDragon(5);
		setClickRange(gdraw.getGridSide() * 3.9/10.0);

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

		this.pane.getChildren().add(this.canvas);
		this.pane.getChildren().add(resetButton("重新开始", 50, 50));
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

	public Button resetButton(String text, double cx, double cy)
	{
		Button button = new Button();

		button.setText( text );
		button.setLayoutX( this.gdraw.getWidth() + cx );
		button.setLayoutY( cy );
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
		this.CM = new byte[gdraw.getChessboardRank()+2][gdraw.getChessboardRank()+2];
		return this;
	}

	boolean win(int row, int col)
	{
		if (stat(row, col, 1, 0) >= dragon)
			return true;
		if (stat(row, col, 0, 1) >= dragon)
			return true;
		if (stat(row, col, 1, 1) >= dragon)
			return true;
		if (stat(row, col, 1, -1) >= dragon)
			return true;
		return false;
	}

	int stat(int row, int col, int ra, int ca)
	{
		++row;
		++col;
		int r, c, n=1;
		byte key = CM[row][col];
		r = row + ra;
		c = col + ca;
		while ( CM[r][c] == key ) {
			r += ra;
			c += ca;
			++n;
		}
		r = row - ra;
		c = col - ca;
		while ( CM[r][c] == key ) {
			r -= ra;
			c -= ca;
			++n;
		}
		return n;
	}

/*----- handle -----*/

	public void mouseEvent(MouseEvent event)
	{
		int c[]=click(event.getX(), event.getY());
		if ( c == null || CM [c[0]+1] [c[1]+1] != 0 )
			return;
		this.gdraw.drawChessman(c[0], c[1], flag);
		if ( flag ) {
			CM [c[0]+1] [c[1]+1] = 1;
			flag = false;
		} else {
			CM [c[0]+1] [c[1]+1] = -1;
			flag = true;
		}
		if ( win(c[0], c[1]) )
			System.out.println((flag ? "black" : "white")+" win");
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
