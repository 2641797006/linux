import java.util.ArrayList;

public class BigInt{
	private int sign; // +/-
	private ArrayList<Byte> num;

	public BigInt() { init(null); }
	public BigInt(BigInt big) { init(big); }
/*
public:
	BigInt assign(BigInt); //=
	void set(long); // long to BigInt
	BigInt add(BigInt);
	BigInt sub(BigInt);
	String toString();
*/
	private void init(BigInt big) {
		num = new ArrayList<Byte>();
		if (big == null) {
			num.add((byte)0);
			sign = 1;
		} else
			assign(big);
	}

	public BigInt assign(BigInt big) {
		sign = big.sign;
		return u_assign(big);
	}

	private BigInt u_assign(BigInt big) { // unsign assign
		num.clear();
		num.addAll(big.num);
		return this;
	}

	public BigInt add(BigInt big) {
		return __as(big, sign*big.sign < 0);
	}

	public BigInt sub(BigInt big) {
		return __as(big, sign*big.sign > 0);
	}

	private BigInt __as(BigInt big, boolean flag) {
		if (flag) {
			if (u_sub(big) < 0)
				sign=-sign;
		} else
			u_add(big);
		return this;
	}

	private BigInt u_add(BigInt _big) { // unsign add
		int i, n;

		BigInt big = new BigInt();
		big.assign(_big);
		n = big.num.size();
		for (i=0; i<n; ++i) {
			if (i >= num.size())
				num.add((byte)0);
			num.set(i, (byte)( num.get(i) + big.num.get(i) ) );
			if (num.get(i)>=10)
				carry(i);
		}
		for ( ; i<num.size(); ++i)
			if ( num.get(i) < 10 )
				break;
			else
				carry(i);
		return this;
	}

	private int u_sub(BigInt big) { // unsign sub
		if (abscmp(big) < 0) {
			var big_t = new BigInt(big);
			big_t.bs_sub(this);
			u_assign(big_t);
			return -1;
		}
		bs_sub(big);
		return 0;
	}

	private BigInt bs_sub(BigInt big) { // big - small (unsign)
		int i;
		for (i=0; i<big.num.size(); ++i) {
			num.set(i, (byte)(num.get(i) - big.num.get(i)));
			if (num.get(i)<0)
				borrow(i);
		}
		for ( ; i<num.size(); ++i) {
			if (num.get(i)>=0)
				break;
			borrow(i);
		}
		rm_zero();
		return this;
	}

	public void set(long n) {
		int i;
		byte b;
		num.clear();
		if (n<0) {
			sign=-1;
			n=-n;
		} else
			sign = 1;
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

		if (sign < 0)
			str.append('-');
		while (--i>=0)
			str.append(num.get(i));
		return str.toString();
	}

	private int abscmp(BigInt big) { // num compare, ignore sign
		int diff = num.size() - big.num.size();
		if (diff != 0)
			return diff;
		int i = num.size();
		while (--i>=0) {
			diff = num.get(i) - big.num.get(i);
			if (diff != 0)
				return diff;
		}
		return 0;
	}

	private void carry(int index) { // num.get(index) >= 10
		num.set(index, (byte)(num.get(index)-10));
		if (++index < num.size())
			num.set(index, (byte)(num.get(index)+1));
		else
			num.add((byte)1);
	}

	private void borrow(int index) { // num.get(index) < 0
		num.set(index, (byte)(num.get(index)+10));
		++index;
		num.set(index, (byte)(num.get(index)-1));
	}

	private void rm_zero() { // remove the high zero
		int i = num.size();
		while (--i>=1)
			if (num.get(i) == 0)
				num.remove(i);
			else
				break;
	}
}
