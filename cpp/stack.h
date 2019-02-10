#ifndef _STACK_H_
#define _STACK_H_

#ifndef _GLIBCXX_VECTOR
#include <vector>
#endif

#define __tt(T)	template <typename T>

namespace pk{
using namespace std;

__tt(T)
class stack{
  public:
	void push(T const&);
	void pop(T&);

  private:
	vector<T> elem;
};

__tt(T)
void
stack<T>::push(T const& t)
{
	elem.push_back(t);
}

__tt(T)
void
stack<T>::pop(T& t)
{
	if(elem.size()<1)
		return;
	t=elem[elem.size()-1];
	elem.pop_back();
}

} //namespace pk{}

#undef __tt

#endif
