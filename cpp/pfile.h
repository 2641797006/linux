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

#define PF_LINES_INIT	0x0001

namespace __pfile{
using namespace std;

class pfile : virtual public fstream
{
  public:
	void print();					//输出所有行
	void print(int line);				//输出第line行
	void insert(int line, string& s);		//把s插入到第line行
	void insert(int line, int num, string& s);	//把num个s插入到第line行
	void erase(int line);				//删除第line行
	void erase(int line1, int line2);		//删除第line1行到第line2行(含line1行)
	void push(string& s);				//在最后一行后面增加一行s
	void pop(string& s);				//用s返回最后一行, 并删除最后一行
	void traverse(void (*visit)(string&));		//用visit函数遍历所有行
	void save();					//保存文件
	void save(const char *fname);			//以文件名fname保存文件

	void swap(int line1, int line2);		//交换第line1行与第line2行
	void wrap(int line, int pos);			//把第line行从pos位置截断为2行
	void escape(const char *str);			//转义字符集str( " -> \" )
	void erase_blankline();				//删除空行

	string file_name();				//返回文件名
	void init(const char* fname, ios::openmode mode);	//打开文件fname进行初始化
	pfile(const char* fname, ios::openmode mode);	//打开文件fname

  protected:
	string fname;					//文件名
	vector<string> lines;				//存储每一行

  private:
	int status=0;					//状态
	void initlines();				//初始化lines
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
	if(status&PF_LINES_INIT)
		return;
	open(fname, mode);
	if(!is_open()){
		cerr<<"Cannot open file: \""<<fname<<"\""<<endl;
		return;
	}
	this->fname.assign(fname);
	initlines();
}

inline string pfile::file_name()
{
	return fname;
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
	status|=PF_LINES_INIT;
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
