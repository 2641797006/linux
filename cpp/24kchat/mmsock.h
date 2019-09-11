#ifndef _MMSOCK_H_
#define _MMSOCK_H_

#ifndef _GLIBCXX_IOSTREAM
#include <iostream>
#endif

#ifndef _GLIBCXX_LIST
#include <list>
#endif

#ifndef _GLIBCXX_STRING
#include <string>
#endif

#ifndef _STRING_H
#include <string.h>
#endif

#ifndef _KSCP_H_
#include "kscp.h"
#endif

#ifndef _GETCH_H_
#include "getch.h"
#endif

#include <stdarg.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MM_PORT	(9999)
#define MM_RWFLAG	( 0 )
#define MM_IS_TYPING	0x1

namespace _24k {
using namespace std;

void kerr(const char *fmt, ...);

class MMSOCK {
  public:
	using ADDR = struct sockaddr_in;
	using ADDR_O = struct sockaddr;
	enum TYPE{ SERVER, CLIENT };

  private:
	TYPE _type;
	uint32_t flags;
	int server_sd, client_sd;
	ADDR server_addr, client_addr;
	char *buffer;
	KSCP kscp;
	list<string> ls_message;
	static const string exit_code;

	void set_type(TYPE t) { _type = t; }
	int typing(string&);


  public:
	MMSOCK(string const& ip, TYPE type, int port=MM_PORT);
	~MMSOCK();
	
	TYPE type() { return _type; }
	bool bind();
	bool listen(int n=24);
	bool accept();
	string client_ip() { return inet_ntoa(client_addr.sin_addr); }
	string server_ip() { return inet_ntoa(server_addr.sin_addr); }
	bool connect();

	string recv();
	string recv_s();
	string recv_wait_s();
	list<string>&& messages() { return move(ls_message); }
	bool send();
	bool send(string const&);
	bool send_s();
	bool send_s(string const&);
	bool send_wait_s();

	int get_sd() { return type()==SERVER ? client_sd : server_sd; }
	bool is_typing() { return flags & MM_IS_TYPING; }
	string get_exit_code() { return exit_code; }
};

const string MMSOCK::exit_code = "\rABC傻逼\n";

MMSOCK::MMSOCK(string const& ip, TYPE type, int port)
{
	set_type(type);
	flags = 0;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip.size() ? ip.c_str() : "0.0.0.0");
	server_addr.sin_port = htons(port);

	server_sd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sd < 0)
		kerr("socket() error\n");
	buffer = new char[BUFSIZ+1];
}

MMSOCK::~MMSOCK()
{
	free(buffer);
	close(server_sd);
	if (type() == SERVER)
		close(client_sd);
}

bool
MMSOCK::bind()
{
	if (::bind(server_sd, (ADDR_O*)&server_addr, sizeof(ADDR_O)) < 0) {
		kerr("bind() error\n");
		return false;
	}
	return true;
}

bool
MMSOCK::listen(int n)
{
	if (::listen(server_sd, n) < 0) {
		kerr("listen() error\n");
		return false;
	}
	return true;
}

bool
MMSOCK::accept()
{
	if (type() == CLIENT) {
		kerr("client use accept()\n");
		return false;
	}
	socklen_t sin_size = sizeof(ADDR);
	client_sd = ::accept(server_sd, (ADDR_O*)&client_addr, &sin_size);
	if (client_sd < 0) {
		kerr("accept() error\n");
		return false;
	}
	return true;
}

bool
MMSOCK::connect()
{
	if (::connect(server_sd, (ADDR_O*)&server_addr, sizeof(ADDR_O)) < 0) {
		kerr("connect() error\n");
		return false;
	}
	return true;
}

string
MMSOCK::recv()
{
	string s;
	int len = ::recv(type()==SERVER ? client_sd : server_sd, buffer, BUFSIZ, MM_RWFLAG);
	if (len < 0) {
		kerr("MMSOCK> recv error\n");
		return s;
	}
	buffer[len] = 0;
	s = buffer;
	if ( s == exit_code ) {
		cout<<"Connection to "<<(type()==SERVER ? client_ip() : server_ip())
			<<" closed by remote host"<<endl;
		exit(24);
	}
	return s;
}

string
MMSOCK::recv_s()
{
	string s = move(recv());
	return s.size() ? kscp.decrypt(s) : s;
}

string
MMSOCK::recv_wait_s()
{
	string s;
	s = move(recv_s());
	if ( s.size() && is_typing() )
		ls_message.push_back(move(s));
	return s;
}

bool
MMSOCK::send_wait_s()
{
	string s;
	typing(s);
	flags &= ~MM_IS_TYPING;
	return send(kscp.encrypt(s));
}

bool
MMSOCK::send()
{
	string s;
	typing(s);
	return send(s);
}

bool
MMSOCK::send(string const& s)
{
	if (::send(type()==SERVER ? client_sd : server_sd, s.c_str(), s.size(), MM_RWFLAG) < 0) {
		kerr("MMSOCK> send error\n");
		return false;
	}
	flags &= ~MM_IS_TYPING;
	return true;
}

bool
MMSOCK::send_s()
{
	string s;
	typing(s);
	return send(kscp.encrypt(s));
}

bool
MMSOCK::send_s(string const& s)
{
	return send(kscp.encrypt(s));
}

int
MMSOCK::typing(string& s)
{
	int c;
	c = getche();
	if (c == '\n')
		return -1;
	flags |= MM_IS_TYPING;
	cin.putback(c);
	getline(cin, s);
	return 0;
}

void
kerr(const char *fmt, ...)
{
#ifndef KERR_NOT_PRINT
	va_list ap;
	va_start(ap, fmt);
	fprintf(stderr, "\nkerr> ");
	vfprintf(stderr, fmt, ap);
	va_end(ap);
#endif

#ifndef KERR_NOT_EXIT
	exit(24);
#endif
}

} // namespace _24k;

#endif // _MMSOCK_H_

