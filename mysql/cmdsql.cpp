#include <iostream>
#include <string>
#include <list>
#include <pwd.h>
#include <unistd.h>
#include <ctype.h>

#define NDEBUG

using namespace std;

class MySQL {
  private:
	string username;
	string password;
	string database;

  public:
	MySQL(string const& u, string const& p) {
		username = u, password = p;
	}

	MySQL(string const& u) {
		new(this) MySQL(u, "");
	}

	string& u() { return username; }
	string& p() { return password; }
	string& o() { return database; }

	void set_database(string const& o) {
		database = o;
	}
};

string first_word(string const&);
string next_word(string const&);
int word_index=0;

int main(int argc, char **argv)
{
	struct passwd *user_info = getpwuid( getuid() );

	string s, s1, s2, cmd, head="mysql -u ";
	MySQL mysql(user_info->pw_name);
	list<string> ls;

	for (;;) {
		cout<<"CMDsql ["<<(mysql.o().size() ? mysql.o() : "(SB)")<<"]> ";
		getline(cin, s);
		if ( ! s.size() )
			continue;
		s1 = first_word(s);
		if ( ! s1.size() )
			continue;
		if (s1 == "exit") {
			cout<<"\033[1;36m"<<"Bye\n"<<"\033[0m";
			break;
		}
		if (s1 == "use") {
			s2 = next_word(s);
			mysql.set_database( s2.size() ? s2 : "" );
			if ( s2.size() )
				cout<<"\033[1;37m"<<"Database changed\n"<<"\033[0m";
			else
				cout<<"\033[1;31m"<<"Database changed to None\n"<<"\033[0m";
			continue;
		}
		cmd = head + mysql.u() + " -e " + '\"' + s + '\"';
		if ( mysql.o().size() )
		cmd += " -o " + mysql.o();
#ifndef NDEBUG
		cout<<cmd<<endl;
#endif
		system(cmd.c_str());
	}

}

string
first_word(string const& s)
{
	int i=0, begin;
	string word;

	while (isspace(s[i]))
		++i;
	begin = i;
	while (isalpha(s[i]))
		++i;
	if (isspace(s[i]) || (! s[i] && begin != i))
		word = s.substr(begin, i-begin);
	word_index = i;
	return word;
}

string
next_word(string const& s)
{
	int i=word_index, begin;
	string word;

	while (isspace(s[i]))
		++i;
	begin = i;
	while (isalpha(s[i]))
		++i;
	if (isspace(s[i]) || (! s[i] && begin != i))
		word = s.substr(begin, i-begin);
	return word;
}

