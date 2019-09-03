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
	list<string*> ls_result;
	int col;
	int is_connect;
	int is_save;

	string username;
	string password;
	string ip;
	string dbname;

  public:
	using RES = list<string*>;
	MMSQL(string const& u, string const& p, string const& i, string const& db="")
	{
		username=u, password=p, ip=i, dbname=db;
		mysql = mysql_init(NULL);
		res = NULL; col=0;
		is_connect = false, is_save = true;
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

	bool query(string const& cmd)
	{
		is_save = false;
		return ! mysql_real_query(mysql, cmd.c_str(), cmd.size());
	}

	RES& result();
	RES&& move_result() { result(); return move(ls_result); }
	int result_col() { return col; }

	string error() { return mysql_error(mysql); }

	void print() { print(ls_result); }
	void print(RES const&);
};

void
MMSQL::print(MMSQL::RES const& res)
{
	for (auto x : res) {
		for (int i=0; i<result_col(); ++i)
			cout<<x[i]<<' ';
		cout<<'\n';
	}
}

MMSQL::RES&
MMSQL::result()
{
	if ( ! is_save ) {
		is_save = true;
		int i;
		string *line;

		if ( res )
			mysql_free_result(res);
		res = mysql_store_result(mysql);
		if ( ! res )
			return ls_result;

		for (auto x : ls_result)
			delete[] x;
		ls_result.clear();

		col = mysql_num_fields(res);
		while ( (row = mysql_fetch_row(res)) ) {
			line = new string[col];
			for (i=0; i<col; ++i)
				line[i] = row[i] ? row[i] : "NULL";
			ls_result.push_back(line);
		}
	}
	return ls_result;
}

} // namespace _24k;

#endif // _MMSQL_H_

