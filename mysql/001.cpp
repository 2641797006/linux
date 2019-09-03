#include <iostream>
#include <string>
#include <mysql/mysql.h>
using namespace std;

int main()
{
	MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;

	string username("cpplay");
	string password("123456");
	string ip("127.0.0.1");
	string dbname("tmp");
	string tablename("Student");

	mysql = mysql_init(NULL);
	if ( ! mysql ) {
		cout<<"init error"<<endl;
		return -1;
	}
	if (mysql_real_connect(mysql, ip.c_str(), username.c_str(), password.c_str(), dbname.c_str(), 3306, NULL, 0))
		cout<<"connect OK"<<endl;
	else
		cout<<"Error"<<endl;
}

