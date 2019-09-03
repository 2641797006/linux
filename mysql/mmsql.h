#ifndef _MMSQL_H_
#define _MMSQL_H_

#ifndef _GLIBCXX_LIST
#include <list>
#endif

#ifndef _GLIBCXX_STRING
#include <string>
#endif

#include <mysql/mysql.h>

namespace _24k {
using namespace std;

class MMSQL {
  private:
	MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int query_code;
	list<string*> ls_result;
	int col;
	int is_connect;

	string username;
	string password;
	string ip;
	string dbname;

  public:
	using RES = list<string*>&;
	MMSQL(string const& u, string const& p, string const& i, string const& db="")
	{
		username=u, password=p, ip=i, dbname=db;
		mysql = mysql_init(NULL);
		res = NULL; col=0;
	}

	~MMSQL()
	{
		close();
	}

	void set_dbname(string const& db) { dbname = db; mysql_select_db(mysql, db.c_str()); }
	string const& get_dbname() { return dbname; }

	bool connect()
	{
		is_connect = mysql_real_connect( mysql, ip.c_str(),
			username.c_str(), password.c_str(),
			dbname.c_str(), 3306, NULL, 0) == NULL ? false : true;
		return is_connect;
	}

	void close()
	{
		if ( ! is_connect )
			return;
		if ( res )
			mysql_free_result(res);
		mysql_close(mysql);
		is_connect = false;
	}

	bool query(string const&);
	RES result() { return ls_result; }
	int result_col() { return col; }

	string error() { return mysql_error(mysql); }
};

bool
MMSQL::query(string const& cmd)
{
	query_code = mysql_real_query(mysql, cmd.c_str(), cmd.size());
	if ( ! query_code ) {
		int i=0;
		string *line;
		for (auto x : ls_result)
			delete[] x;
		if ( res )
			mysql_free_result(res);
		res = mysql_store_result(mysql);
		if ( ! res )
			return true;
		col = mysql_num_fields(res);
		while ( (row = mysql_fetch_row(res)) ) {
			line = new string[col];
			for (i=0; i<col; ++i)
				line[i] = row[i];
			ls_result.push_back(line);
		}
		return true;
	}
	return false;
}


} // namespace _24k;

#endif // _CPPSQL_H_

