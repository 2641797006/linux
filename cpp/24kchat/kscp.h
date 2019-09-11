#ifndef _KSCP_H_
#define _KSCP_H_

#ifndef _GLIBCXX_STRING
#include <string>
#endif

namespace _24k {
using namespace std;

class KSCP {
  public:
	using BYTE = unsigned char;
	string encrypt(string const&);
	string decrypt(string const&);
};

string
KSCP::encrypt(string const& ds)
{
	BYTE last, c;
	string es;

	last = 0x7;
	for (unsigned int i=0; i<ds.size(); ++i) {
		c = ds[i];
		last = last<<5 | c>>3;
		es.push_back(last);
		last = c;
	}
	last = last<<5 | 0x1f;
	es.push_back(last);
	return es;
}

string
KSCP::decrypt(string const& es)
{
	BYTE last, c, c1;
	string ds;

	last = es[0];
	for (unsigned int i=1; i<es.size(); ++i) {
		c1 = es[i];
		c = last<<3 | c1>>5;
		ds.push_back(c);
		last = c1;
	}
	return ds;
}

} // namespace _24k

#endif // _KSCP_H_

