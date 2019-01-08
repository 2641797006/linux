#ifndef _PFILE_H_
#define _PFILE_H_

#ifndef _GLIBCXX_FSTREAM
#include <fstream>
#endif

#ifndef _GLIBCXX_VECTOR
#include <vector>
#endif

#ifndef _GLIBCXX_STRING
#include <string>
#endif

namespace __pfile{
using namespace std;

class pfile : public fstream
{
  public:
	void print();
	void print(ofstream &out);
	inline void print(int line);
	void save();
	pfile(const char* fname, ios::openmode mode);

  private:
	vector<string> lines;
	string fname;
};

pfile::pfile(const char* fname, ios::openmode mode=ios::in|ios::out) : fstream(fname,mode)
{
	string s;
	char *buf=new char[0x1000];

	this->fname.assign(fname);
	this->fname.append(".pfile");
	while(!this->eof()){
		this->getline(buf, 0x1000);
		s.assign(buf);
		s.append(1, '\n');
		lines.push_back(s);
	}
	this->clear();

	lines.pop_back();
	delete[] buf;
}

void pfile::print()
{
	int i, n=lines.size();
	for(i=0;i<n;i++)
		cout<<lines[i];
}

void pfile::print(ofstream &out)
{
	int i, n=lines.size();
	for(i=0;i<n;i++)
		out<<lines[i];
}

inline void pfile::print(int line)
{
	cout<<lines[line];
}

void pfile::save()
{
	int i, n=lines.size();
	ofstream out;
	out.open(fname.c_str(), ios::out|ios::trunc);
	print(out);
	out.close();
}

}//namespace __pfile

#endif
