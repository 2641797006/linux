#ifndef _MD5SUM_H_
#define _MD5SUM_H_

namespace _24k{
using namespace std;

class md5sum
{
  public:
	string const& operator()(string const&);
	string const& operator()(string const& str, string const& salt){return (*this)(str+salt);}

  private:
	uint32_t A, B, C, D;
	uint32_t a, b, c, d;
	uint32_t x[16];
	string s_null;
	void init(){A=0x67452301, B=0xefcdab89, C=0x98badcfe, D=0x10325476;}
	void loop();
};

} //namespace _24k

#endif
