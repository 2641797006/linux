import java.util.ArrayList;

public class BigInt{
	public BigInt(){num = new ArrayList<Byte>(); num.add((byte)0); sign = 0;}

	public void assign(BigInt bigint) {
		num.clear();
		sign = bigint.sign;
		num.addAll(bigint.num);
	}

	public void add(BigInt _bigint) {
		int i;
		BigInt bigint = new BigInt();
		bigint.assign(_bigint);
		for (i=0; i<bigint.num.size(); ++i) {
			if (i >= num.size())
				num.add((byte)0);
			num.set(i, (byte)(num.get(i) + bigint.num.get(i)));
			if (num.get(i)>=10) {
				num.set(i, (byte)(num.get(i)-10));
				if (i+1<num.size())
					num.set(i+1, (byte)(num.get(i+1)+1));
				else
					num.add((byte)1);
			}
		}
		while ( i<num.size() ) {
			if (num.get(i)<10)
				break;
			num.set(i, (byte)(num.get(i)-10));
			if (++i<num.size())
				num.set(i, (byte)(num.get(i)+1));
			else
				num.add((byte)1);
		}
	}

	public void __sub(BigInt bigint) { // big - small
		int i;
		for (i=0; i<bigint.num.size(); ++i) {
			num.set(i, (byte)(num.get(i) - bigint.num.get(i)));
			if (num.get(i)<0) {
				num.set(i, (byte)(num.get(i)+10));
				num.set(i+1, (byte)(num.get(i+1)+1));
			}
		}
		rm_zero();
	}

	public void set(long n) {
		int i;
		byte b;
		num.clear();
		if (n<0) {
			sign=-1;
			n=-n;
		} else
			sign = 0;
		if ( n == 0 )
			num.add((byte)0);
		while ( n != 0 ) {
			b = (byte)(n%10);
			n /= 10;
			num.add(b);
		}
	}

	public String toString() {
		int i = num.size();
		var str = new StringBuilder();

		if (sign != 0)
			str.append('-');
		while (--i>=0)
			str.append(num.get(i));
		return str.toString();
	}

	private carry(int index) {
		
	}

	private void rm_zero() {
		int i = num.size();
		while (--i>=1)
			if (num.get(i) == 0)
				num.remove(i);
			else
				break;
	}

	private int sign;
	private ArrayList<Byte> num;
}
