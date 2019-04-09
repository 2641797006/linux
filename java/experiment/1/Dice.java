import java.util.Random;

public class Dice {
	Random random;
	int last;
	int current;

	Dice() {
		this.random = new Random();
		this.last = 0;
		this.current = 0;
	}

	public int dice() {
		this.last = this.current;
		this.current = random.nextInt(6) + 1;
		return this.current;
	}

	public int current() {
		return this.current;
	}

	public int last() {
		return this.last;
	}

}
