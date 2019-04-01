import java.lang.Math;
import javafx.scene.paint.Paint;
import javafx.scene.paint.Color;
import javafx.event.EventHandler;
import javafx.scene.input.MouseEvent;
import javafx.scene.canvas.GraphicsContext;

public class Gomoku extends GomokuDraw {
	// 当前棋子颜色
	boolean flag;
	// 有效点击范围
	double click_range;
	// 星位色彩宽高
	Paint star_stroke, star_fill;
	double star_width, star_height;
	byte[][] CM;
	//
	int dragon;

	public Gomoku()
	{
		flag = false;
		dragon = 5;
		CM = new byte[this.chessboard_row+2][this.chessboard_col+2];
		setClickRange(this.grid_width * 3.9/10.0);
		setStarColor(null, Color.web("#888A85"));
		setStarSize(this.grid_width/4.0, this.grid_height/4.0);
		setStar();
		canvas.setOnMouseClicked(new Message(this));
	}

	Gomoku setStarColor( Paint stroke, Paint fill )
	{
		this.star_stroke = stroke;
		this.star_fill = fill;
		return this;
	}

	Gomoku setStarSize( double width, double height )
	{
		this.star_width = width;
		this.star_height = height;
		return this;
	}

	public Gomoku setStar()
	{
		setStar( 3, 3);
		setStar( 9, 3);
		setStar(15, 3);
		setStar( 3, 9);
		setStar( 9, 9);
		setStar(15, 9);
		setStar( 3, 15);
		setStar( 9, 15);
		setStar(15, 15);
		return this;
	}

	Gomoku setStar(int row, int col)
	{
		return setStar( getGC(), row, col );
	}

	Gomoku setStar(GraphicsContext gc, int row, int col)
	{
		setChessman( gc, row, col, this.star_stroke, this.star_fill, this.star_width, this.star_height,
				this.chessboard_startX, this.chessboard_startY,
				this.grid_width, this.grid_height );
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

	public void handle(MouseEvent event)
	{
		int c[]=click(event.getX(), event.getY());
		if ( c == null || CM [c[0]+1] [c[1]+1] != 0 )
			return;
		setChessman(c[0], c[1], flag);
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

	public Gomoku setClickRange(double d)
	{
		this.click_range = d;
		return this;
	}

	int[] click(double cx, double cy)
	{
		int row, col;
		if (cx < this.chessboard_startX-this.click_range || cx > this.chessboard_endX+this.click_range)
			return null;
		if (cy < this.chessboard_startY-this.click_range || cy > this.chessboard_endY+this.click_range)
			return null;
		cx -= this.chessboard_startX;
		cy -= this.chessboard_startY;
		row = (int) ( cy / this.grid_height );
		col = (int) ( cx / this.grid_width );
		if ( cx % this.grid_width > this.grid_width - this.click_range )
			++col;
		else if ( cx % this.grid_width > this.click_range )
			return null;
		if ( cy % this.grid_height > this.grid_height - this.click_range )
			++row;
		else if ( cy % this.grid_height > this.click_range )
			return null;
		if ( Math.pow(cx - col*this.grid_width, 2) + Math.pow(cy - row*this.grid_height, 2)
				> Math.pow(this.click_range, 2) )
			return null;
		return new int[]{row, col};
	}

	class Message implements EventHandler<MouseEvent>
	{
		Gomoku gomoku;

		public Message(Gomoku gomoku)
		{
			this.gomoku = gomoku;
		}

		public void handle(MouseEvent event)
		{
			gomoku.handle(event);
		}
	}
}
