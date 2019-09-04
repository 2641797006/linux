#ifndef _MMSQL_H_
#define _MMSQL_H_

#ifndef _GLIBCXX_LIST
#include <list>
#endif

#ifndef _GLIBCXX_STRING
#include <string>
#endif

#include <mysql/mysql.h>

#define MMSQL_CONNECT	0x1
#define MMSQL_SAVE	0x2

namespace _24k {
using namespace std;

class MMSQL {
 private:
	class MMLINE{
	  private:
		string *arr;
		size_t _size;

	  public:
		MMLINE(int n) { arr = new string[n]; _size = n; }
		MMLINE(MMLINE const&) = delete;
		MMLINE(MMLINE && other) { *this = move(other); }
		~MMLINE() { delete[] arr; }
		void operator= (MMLINE const&) = delete;
		void operator= (MMLINE && other)
			{ arr = other.arr, _size = other._size, other.arr = new string[other.size()]; }

		int size() const { return _size; }
		string& operator[] (int i) const { return arr[i]; }

		friend ostream& operator<< (ostream&, MMLINE const&);
	};

	MYSQL *mysql;
	list<MMLINE> ll;
	uint32_t flags;

	string username;
	string password;
	string ip;
	unsigned int port;
	string dbname;

  public:
	using RES = list<MMLINE>;
	using LINE = MMLINE;

	MMSQL(string const& u, string const& p, string const& i, unsigned int port=3306, string const& db="");
	MMSQL(MMSQL const&) = delete;
	MMSQL(MMSQL && mm) { *this = move(mm); }
	~MMSQL() { close(); }
	void operator= (MMSQL const&) = delete;
	void operator= (MMSQL &&);

	void set_dbname(string const& db) { dbname = db; mysql_select_db(mysql, db.c_str()); }
	string const& get_dbname() { return dbname; }

	bool connect();
	void close();
	bool query(string const&);
	RES&& result();
	friend ostream& operator<< (ostream&, RES const&);

	string error() { return mysql_error(mysql); }
};

MMSQL::MMSQL(string const& u, string const& p, string const& i, unsigned int port, string const& db)
{
	username=u, password=p, ip=i;
	this->port=port, dbname=db;
	mysql = mysql_init(NULL);
	flags = MMSQL_SAVE;
}

void
MMSQL::operator= (MMSQL && mm)
{
	this->mysql = mm.mysql;
	this->ll.swap(mm.ll);
	this->flags = mm.flags;
	this->username.swap(mm.username);
	this->password.swap(mm.password);
	this->ip.swap(mm.ip);
	this->port = mm.port;
	this->dbname.swap(mm.dbname);

	mm.mysql = NULL;
}

bool
MMSQL::connect()
{
	flags = mysql_real_connect( mysql, ip.c_str(),
		username.c_str(), password.c_str(),
		dbname.c_str(), port, NULL, 0) == NULL
		? flags & ~MMSQL_CONNECT
		: flags | MMSQL_CONNECT;
	return flags & MMSQL_CONNECT;
}

void
MMSQL::close()
{
	if ( ! (flags & MMSQL_CONNECT) )
		return;
	mysql_close(mysql);
	flags &= ~MMSQL_CONNECT;
}

bool
MMSQL::query(string const& cmd)
{
	flags &= ~MMSQL_SAVE;
	return ! mysql_real_query(mysql, cmd.c_str(), cmd.size());
}

MMSQL::RES&&
MMSQL::result()
{
	if ( ! (flags & MMSQL_SAVE) ) {
		flags |= MMSQL_SAVE;

		MYSQL_RES *res = mysql_store_result(mysql);
		if ( ! res )
			return move(ll);

		int i, col;
		MYSQL_ROW row;

		ll.clear();
		col = mysql_num_fields(res);
		LINE line(col);
		while ( (row = mysql_fetch_row(res)) ) {
			for (i=0; i<col; ++i)
				line[i] = row[i] ? row[i] : "NULL";
			ll.push_back(move(line));
		}

		mysql_free_result(res);
	}
	return move(ll);
}

ostream&
operator<< (ostream &os, MMSQL::LINE const& line)
{
	int i;
	for (i=0; i<line.size(); ++i)
		os<<line[i]<<' ';
	return os<<'\n';
}

ostream&
operator<< (ostream &os, MMSQL::RES const& res)
{
	for (auto &x : res)
		os<<x;
	return os;
}

} // namespace _24k;

#endif // _MMSQL_H_

