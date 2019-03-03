public class string{
	public StringBuilder _str;

	public string() {_str = new StringBuilder();}
	public string(String s) {_str = new StringBuilder(s);}

	public void push_back(char c) {_str.append(c);}
	public void pop_back() {_str.deleteCharAt(_str.length()-1);}

	public int size() {return _str.length();}
	public int length() {return _str.length();}
	public int capacity() {return _str.capacity();}
	public void resize(int i) {_str.setLength(i);}
	public void reserve(int i) {_str.ensureCapacity(i);}
	public void clear() {_str.setLength(0);}
	public boolean empty() {return _str.length()==0 ? true : false;}
	public void shrink_to_fit() {_str.trimToSize();}

	public char at(int pos) {return _str.charAt(pos);}
	public char front() {return _str.charAt(0);}
	public char back() {return _str.charAt(_str.length()-1);}

	public string append(String s) {_str.append(s); return this;}
	public string append(String s, int pos, int n){_str.append(s, pos, pos+n); return this;}
	public string append(String s, int n){_str.append(s, 0, n); return this;}
	public string append(int n, char c) {while(n-->0)_str.append(c); return this;}

	public string assign(String s) {_str = new StringBuilder(s); return this;}
	public string assign(String s, int pos, int n) {_str = new StringBuilder(); _str.append(s, pos, pos+n); return this;}
	public string assign(String s, int n) {_str = new StringBuilder(); _str.append(s, 0, n); return this;}
	public string assign(int n, char c) {_str = new StringBuilder(); while(n-->0)_str.append(c); return this;}

	public string insert(int pos, String s) {_str.insert(pos, s); return this;}
	public string insert(int pos, String s, int pos1, int n) {_str.insert(pos, s, pos1, pos1+n); return this;}
	public string insert(int pos, String s, int n) {_str.insert(pos, s, 0, n); return this;}
	public string insert(int pos, int n, char c)
		{StringBuilder s = new StringBuilder(); while(n-->0)s.append(c); _str.insert(pos, s); return this;}

	public string erase(int pos) {_str.deleteCharAt(0); return this;}
	public string erase(int pos, int n) {_str.delete(pos, pos+n); return this;}

	public string replace(int pos, int n, String s) {_str.replace(pos, pos+n, s); return this;}
	public string replace(int pos, int n, String s, int pos1, int n1)
		{_str.replace(pos, pos+n, s.substring(pos1, pos1+n)); return this;}
	public string replace(int pos, int n, String s, int n1) {_str.replace(pos, pos+n, s.substring(0, n1)); return this;}
	public string replace(int pos, int n, int n1, char c)
		{StringBuilder s = new StringBuilder(); while(n1-->0)s.append(c); _str.replace(pos, pos+n, s.toString()); return this;}

	public String c_str() {return _str.toString();}
	public String toString() {return _str.toString();}
	public void setCharAt(int pos, char c) {_str.setCharAt(pos, c);}

	public int copy(char[] buf, int i, int n) {_str.getChars(0, n, buf, i); return _str.length()>=n ? n : _str.length();}
	public int copy(char[] buf, int i, int n, int pos)
		{_str.getChars(pos, pos+n, buf, i); return _str.length()>=pos+n ? n : _str.length()-pos;}

	public int find(String s) {return _str.indexOf(s);}
	public int find(String s, int pos) {return _str.indexOf(s, pos);}
	public int find(String s, int pos, int n) {return _str.indexOf(s.substring(0, n), pos);}
	public int find(char c) {return _str.indexOf(""+c);}
	public int find(char c, int pos) {return _str.indexOf(""+c, pos);}

	public int rfind(String s) {return _str.lastIndexOf(s);}
	public int rfind(String s, int pos) {return _str.lastIndexOf(s, pos);}
	public int rfind(String s, int pos, int n) {return _str.lastIndexOf(s.substring(0, n), pos);}
	public int rfind(char c) {return _str.lastIndexOf(""+c);}
	public int rfind(char c, int pos) {return _str.lastIndexOf(""+c, pos);}

//	find_first_of
//	find_last_of
//	find_first_not_of
//	find_last_not_of

	public String substr() {return _str.toString();}
	public String substr(int pos) {return _str.substring(pos);}
	public String substr(int pos, int n) {return _str.substring(pos, pos+n);}

	public int compare(String s) {return _str.toString().compareTo(s);}
	public int compare(int pos, int n, String s) {return _str.substring(pos, pos+n).toString().compareTo(s);}
	public int compare(int pos, int n, String s, int pos1, int n1)
		{return _str.substring(pos, pos+n).toString().compareTo(s.substring(pos1, pos1+n1));}
	public int compare(int pos, int n, String s, int n1)
		{return _str.substring(pos, pos+n).toString().compareTo(s.substring(0, n1));}

	public void print() {System.out.print(_str);}
	public void println() {System.out.println(_str);}
}
