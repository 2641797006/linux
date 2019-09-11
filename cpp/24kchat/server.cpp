#include <iostream>
#include <string>
#include <thread>
#include <csignal>
#include "mmsock.h"

using namespace _24k;
using namespace std;

void t_recv(MMSOCK*);
void t_send(MMSOCK*);
void t_check(MMSOCK*);

MMSOCK *global_mmsock = NULL;
void signal_handler(int signal);

int main()
{
	cout<<"MMSOCK 4.1 * Writen by 24k"<<endl;
	MMSOCK mmsock("", MMSOCK::SERVER, 9998);
	mmsock.bind();
	if ( mmsock.listen(16) )
		cout<<"MMSOCK> listen begin ..."<<endl;
	cout<<"MMSOCK> accept begin ..."<<endl;
	if ( mmsock.accept() )
		cout<<"MMSOCK> accept OK"<<endl;
	cout<<"MMSOCK> client ip = "<<mmsock.client_ip()<<endl;

	global_mmsock = &mmsock;
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);

	thread tr(t_recv, &mmsock);
	thread tw(t_send, &mmsock);
	thread tc(t_check, &mmsock);

	tr.join();
	tw.join();
	tc.join();
}

void
t_recv(MMSOCK* mmsock)
{
	string s;
	for (;;) {
		s = mmsock->recv_wait_s();
		if ( s.size() )
			cout<<"\n\033[1;37mMMSOCK.recv_s()> \033[1;36m"<<s<<"\033[0m"<<endl;
	}
}

void
t_send(MMSOCK* mmsock)
{
	for (;;) {
		mmsock->send_wait_s();
		auto messages = mmsock->messages();
		for (auto &x : messages)
			cout<<"\n\033[1;33mMMSOCK.recv_s()> \033[1;36m"<<x<<"\033[0m"<<endl;
	}
}

void
t_check(MMSOCK* mmsock)
{
	int optval, ret;
	socklen_t len = sizeof(optval);
	for (;;) {
		this_thread::sleep_for(1s);
		ret = getsockopt(mmsock->get_sd(), SOL_SOCKET, SO_ERROR, &optval, &len);
		if (optval || ret) {
			if (optval == EPIPE)
				cerr<<"\n\033[1;31mMMSOCK.error()>\033[1;37m broken pipe\033[0m"<<endl;
			else
				cerr<<"\n\033[1;31mgetsockopt> optval = "<<optval<<" ret = "<<ret<<"\033[0m"<<endl;
			mmsock->~MMSOCK();
			exit(0);
		}
	}
}

void
signal_handler(int signal)
{
	global_mmsock->send(global_mmsock->get_exit_code());
	exit(24);
}

