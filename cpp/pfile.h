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
	inline void print(int line);
	void save(const char* fname);
	inline void save();
	pfile(const char* fname, ios::openmode mode);

  private:
	vector<string> lines;
	string fname;
};

pfile::pfile(const char* fname, ios::openmode mode=ios::in|ios::out) : fstream(fname,mode)
{
	string s;
	this->fname.assign(fname);
	this->fname.append(".pfile");
	while(!eof()){
		std::getline(*this, s);
		s.append(1, '\n');
		lines.push_back(s);
	}
	clear();
	lines.pop_back();
}

void pfile::print()
{
	int i, n=lines.size();
	for(i=0;i<n;i++)
		cout<<lines[i];
}

inline void pfile::print(int line)
{
	cout<<lines[line];
}

void pfile::save(const char* fname)
{
	int i, n=lines.size();
	ofstream out;
	out.open(fname, ios::out|ios::trunc);
	for(i=0;i<n;i++)
		out<<lines[i];
	out.close();
}

inline void pfile::save()
{
	save(fname.c_str());
}

}//namespace __pfile

#endif
