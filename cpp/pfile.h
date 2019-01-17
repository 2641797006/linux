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

class pfile : virtual public fstream
{
  public:
	void print();
	void print(int line);
	void insert(int line, string& s);
	void insert(int line, int num, string& s);
	void erase(int line);
	void erase(int line1, int line2);
	void push(string& s);
	void pop(string& s);
	void traverse(void (*visit)(string&));
	void save();
	void save(const char *fname);

	void swap(int line1, int line2);
	void wrap(int line, int pos);
	void escape(const char *str);
	void erase_blankline();

	void init(const char* fname, ios::openmode mode);
	pfile(const char* fname, ios::openmode mode);

  protected:
	string fname;
	vector<string> lines;
	void initlines();
};

pfile::pfile(const char* fname, ios::openmode mode=ios::in|ios::out) : fstream(fname,mode)
{
	string s;
	if(!is_open()){
		cerr<<"Cannot open file: \""<<fname<<"\""<<endl;
		return;
	}
	this->fname.assign(fname);
	initlines();
}

void pfile::init(const char* fname, ios::openmode mode=ios::in|ios::out)
{
	if(is_open())
		return;
	open(fname, mode);
	if(!is_open()){
		cerr<<"Cannot open file: \""<<fname<<"\""<<endl;
		return;
	}
	this->fname.assign(fname);
	initlines();
}

void pfile::initlines()
{
	string s;
	lines.clear();
	while(!eof()){
		lines.push_back(s);
		std::getline(*this, *(lines.end()-1));
	}
	clear();
	seekg(-1, ios::end);
	if(get()=='\n')
		lines.pop_back();
	seekg(0, ios::beg);
	clear();
}

inline void pfile::swap(int line1, int line2)
{
	lines[line1].swap(lines[line2]);
}

void pfile::wrap(int line, int pos)
{
	string s;
	lines.insert(lines.begin()+line+1, s);
	lines[line+1].assign(lines[line], pos);
	lines[line].erase(pos);
}

void pfile::escape(const char *str)
{
	int i;
	vector<string>::iterator iter;
	for(iter=lines.begin(); iter!=lines.end(); iter++)
		for(i=0;;){
			i=iter->find_first_of(str, i);
			if(i!=string::npos){
				iter->insert(i, "\\");
				i+=2;
			}
			else
				break;
		}
}

void pfile::erase_blankline()
{
	int i;
	vector<string>::iterator iter;
	iter=lines.end();
	while(iter--!=lines.begin()){
		for(i=0; i<iter->size(); i++)
			if(!isspace(*(iter->begin()+i)))
				break;
		if(i==iter->size())
			lines.erase(iter, iter+1);
	}
}

void pfile::print()
{
	vector<string>::iterator iter=lines.begin();
	while(iter!=lines.end())
		cout<<*iter++<<'\n';
	cout.flush();
}

inline void pfile::print(int line)
{
	cout<<lines[line]<<endl;
}

inline void pfile::insert(int line, string& s)
{
	lines.insert(lines.begin()+line, s);
}
inline void pfile::insert(int line, int num, string& s)
{
	lines.insert(lines.begin()+line, num, s);
}
	
inline void pfile::erase(int line)
{
	lines.erase(lines.begin()+line, lines.begin()+line+1);
}

inline void pfile::erase(int line1, int line2)
{
	lines.erase(lines.begin()+line1, lines.begin()+line2);
}

inline void pfile::push(string& s)
{
	lines.push_back(s);
}

void pfile::pop(string& s)
{
	if(lines.empty())
		return;
	s.erase();
	s.swap(*(lines.end()-1));
	lines.pop_back();
}

void pfile::traverse(void (*visit)(string&))
{
	vector<string>::iterator iter=lines.begin();
	while(iter!=lines.end())
		visit(*iter++);
}

void pfile::save(const char *fname)
{
	ofstream out(fname, ios::out|ios::trunc);
	vector<string>::iterator iter=lines.begin();
	while(iter!=lines.end())
		out<<*iter++<<'\n';
	out.close();
}

void pfile::save()
{
	string s(fname);
	s.append(".pfile");
	save(s.c_str());
}

}//namespace __pfile

#endif
