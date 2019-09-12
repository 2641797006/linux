#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

condition_variable cv;
mutex m;

string sbc = "ABC傻逼";
int i=0;

void
sb()
{
	cout<<sbc[i++];
	if ( ! sbc[i] ) {
		cout<<endl;
		exit(0);
	}
}

void
f1()
{
	unique_lock<mutex> lk(m);

	sb();
	cv.wait(lk);

	for (;;) {
		sb();
		cv.notify_one();
		cv.wait(lk);
	}
}

void
f2()
{
	unique_lock<mutex> lk(m);

	for (;;) {
		sb();
		cv.notify_one();
		cv.wait(lk);
	}
}

int main()
{
	thread t1(f1), t2(f2);

	t1.join();
	t2.join();
}

