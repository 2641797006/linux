import java.util.Random;

public class t5{
	public static void main(String[] args) //throws java.io.IOException
	{
		d1 = new Dice();
		d2 = new Dice();
		endp = false;
		win = false;
		int i=0, t=0;
		for (;;) {
			if (t==0)
				play1();
			else
				play2();
			++t;
			if (endp)
				break;
			else
				goOn();
		}
		if (win)
			win();
		else
			lose();
	}

	static Dice d1, d2;
	static boolean endp, win;

	static void play1() {
		d1.dice(); d2.dice();
		int sum = d1.current() + d2.current();
		switch (sum) {
			case 7: case 11:
				win = true;
			case 2: case 3: case 12:
				endp = true;
		}
		printf("%d + %d = %d\n", d1.current(), d2.current(), sum);
	}

	static void play2() {
		d1.dice(); d2.dice();
		int sum = d1.current() + d2.current();
		int lastSum = d1.last() + d2.last();
		if (sum == 7)
			endp = true;
		else if (sum == lastSum) {
			endp = true;
			win = true;
		}
		printf("%d + %d = %d\n", d1.current(), d2.current(), sum);
	}

	static void win() { println("Win"); }
	static void lose() { println("Lose"); }
	static void goOn() { println("Go On"); }

	static void print(String s) {System.out.print(s);}
	static void println(String s) {System.out.println(s);}
	static void printf(String fmt, Object... args) {System.out.printf(fmt, args);}
}
