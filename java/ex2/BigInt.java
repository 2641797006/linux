import java.util.ArrayList;

public class BigInt{
	private boolean sign; // +/-
	private ArrayList<Byte> num;
/*
public:
	BigInt();
	BigInt(long);
	BigInt(String);
	BigInt(BigInt);

	BigInt assign(long); // long to BigInt
	BigInt assign(String); // String to BigInt
	BigInt assign(BigInt); //=

	BigInt add(long);
	BigInt add(String);
	BigInt add(BigInt);

	BigInt sub(long);
	BigInt sub(String);
	BigInt sub(BigInt);

	BigInt mul(long);
	BigInt mul(String);
	BigInt mul(BigInt);

	BigInt div(long);
	BigInt div(String);
	BigInt div(BigInt);

	int cmp(long);
	int cmp(String);
	int cmp(BigInt);

	long toLong();
	String toString();
*/

	public BigInt() {
		num = new ArrayList<Byte>();
		num.add((byte)0);
		sign = true;
	}

	public BigInt(long li) { this(); set(li); }
	public BigInt(String s) { this(); set(s); }

	public BigInt(BigInt big) {
		num = new ArrayList<Byte>();
		assign(big);
	}

	private void init(BigInt big) {
		num = new ArrayList<Byte>();
		if (big == null) {
			num.add((byte)0);
			sign = true;
		} else
			assign(big);
	}

	public BigInt assign(long li) {
		set(li);
		return this;
	}

	public BigInt assign(String s) {
		set(s);
		return this;
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

	public BigInt add(long li) {
		return add(new BigInt(li));
	}

	public BigInt add(String s) {
		return add(new BigInt(s));
	}

	public BigInt add(BigInt big) {
		return __as(big, sign!=big.sign);
	}

	public BigInt sub(long li) {
		return sub(new BigInt(li));
	}

	public BigInt sub(String s) {
		return sub(new BigInt(s));
	}

	public BigInt sub(BigInt big) {
		return __as(big, sign==big.sign);
	}

	private BigInt __as(BigInt big, boolean flag) {
		if (flag) {
			if (u_sub(big) < 0)
				sign=!sign;
		} else
			u_add(big);
		zerofix();
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
		if (u_cmp(big) < 0) {
			var big_t = new BigInt(big);
			big_t._bs_sub(this);
			u_assign(big_t);
			return -1;
		}
		_bs_sub(big);
		return 0;
	}

	private BigInt _bs_sub(BigInt big) { // big - small (unsign)
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

	public BigInt mul(long li) {
		return mul(new BigInt(li));
	}

	public BigInt mul(String s) {
		return mul(new BigInt(s));
	}

	public BigInt mul(BigInt big) {
		sign = sign==big.sign ? true : false;
		u_mul(big);
		rm_zero();
		zerofix();
		return this;
	}

	private BigInt u_mul(BigInt big) {
		int i, n;
		BigInt b1, b2;
		if (num.size() <= big.num.size()) {
			b1 = new BigInt(this);
			b2 = new BigInt(big);
		} else {
			b1 = new BigInt(big);
			b2 = new BigInt(this);
		}
		num.clear();
		num.add((byte)0);
		n = b1.num.size();
		for (i=0; i<n; ++i)
			_sg_mul(b2, b1.num.get(i), i);
		return this;
	}

	private BigInt _sg_mul(BigInt big, byte muler, int index) {
		int i, n;
		i = index;
		n = big.num.size() + index;
		for (; i<n; ++i) {
			if (i >= num.size())
				num.add((byte)0);
			num.set(i, (byte) (num.get(i) + big.num.get(i-index)*muler));
			if (num.get(i) >= 10)
				carry(i);
		}
		return this;
	}

	public BigInt div(long li) {
		return div(new BigInt(li));
	}

	public BigInt div(String s) {
		return div(new BigInt(s));
	}

	public BigInt div(BigInt big) {
		if (big.cmp(0) == 0) // x/0 should return null
			return null;
		sign = sign==big.sign ? true : false;
		u_div(big);
		rm_zero();
		zerofix();
		return this;
	}

	private BigInt u_div(BigInt big) { // unsign div
		int i;
		BigInt b1, bq;

		b1 = new BigInt();
		bq = new BigInt();
		i = num.size() - big.num.size();
		bq._en_num(i+1);
		for (; i>=0; --i) {
			b1.num.clear();
			b1._cp_num(i, this);
			bq.num.set(i, (byte)b1._el_div(big));
			_cp_num(b1, i);
			i -= rm_zero();
		}
		u_assign(bq);
		return this;
	}

	private int _el_div(BigInt big) { // unsign && same size
		int i=0;
		while (u_cmp(big) >= 0) {
			_bs_sub(big);
			++i;
		}
		return i;
	}

	private void _cp_num(int index, BigInt big) { // copy big.num[index] to num
		int i, n=big.num.size()-index;
		for (i=0; i<n; ++i)
			num.add(big.num.get(i+index));
	}

	private void _cp_num(BigInt big, int index) { // copy big.num to num[index]
		int i, n=big.num.size()+index;
		for (i=index; i<n; ++i)
			num.set(i, big.num.get(i-index));
		n = num.size();
		while (--n>=i)
			num.remove(n);
	}

	private void _en_num(int n) {
		int i = num.size();
		num.ensureCapacity(n);
		for (; i<n; ++i)
			num.add((byte)0);
	}

	public void set(long n) {
		int i;
		byte b;
		num.clear();
		if (n<0) {
			sign = false;
			n = -n;
		} else
			sign = true;
		if ( n == 0 )
			num.add((byte)0);
		while ( n != 0 ) {
			b = (byte)(n%10);
			n /= 10;
			num.add(b);
		}
	}

	public void set(String str) {
		int i=str.length(), diff;
		sign = true;
		if (str.charAt(0) == '-') {
			sign = false;
			diff = 1;
		} else if (str.charAt(0) == '+')
			diff = 1;
		else
			diff = 0;
		num.clear();
		while (--i>=diff)
			num.add((byte) (str.charAt(i) & ~0x30));
		rm_zero();
		zerofix();
	}

	public String toString() {
		int i = num.size();
		var str = new StringBuilder();

		if (!sign)
			str.append('-');
		while (--i>=0)
			str.append( (char) (num.get(i) | 0x30) );
		return str.toString();
	}

	public long toLong() {
		long li = 0;
		int i = num.size();
		while (--i>=0)
			li = li * 10 + num.get(i);
		return li;
	}

	public int cmp(long li) {
		return cmp(new BigInt(li));
	}

	public int cmp(String s) {
		return cmp(new BigInt(s));
	}

	public int cmp(BigInt big) {
		if (sign != big.sign)
			return sign ? 1 : -1;
		return sign ? u_cmp(big) : -u_cmp(big);
	}

	private int u_cmp(BigInt big) { // num compare, ignore sign
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
		int q = num.get(index)/10;
		num.set(index, (byte)(num.get(index)%10));
		if (++index < num.size())
			num.set(index, (byte)(num.get(index)+q));
		else
			num.add((byte)q);
	}

	private void borrow(int index) { // num.get(index) < 0
		num.set(index, (byte)(num.get(index)+10));
		++index;
		num.set(index, (byte)(num.get(index)-1));
	}

	private int rm_zero() { // remove the high zero
		int i = num.size();
		while (--i>=1)
			if (num.get(i) == 0)
				num.remove(i);
			else
				break;
		return num.size() - i - 1;
	}

	private void zerofix() { // 0 must be +0
		if (num.size()==1 && num.get(0)==0)
			sign = true;
	}
}
