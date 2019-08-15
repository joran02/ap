/*
 * SQLWork.h
 *
 *  Created on: Dec 29, 2016
 *      Author: tla001
 */

#ifndef SQLWORK_H_
#define SQLWORK_H_

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>
#include <mysql_connection.h>

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>


using namespace std;
using namespace sql;

class SQLWork {
public:
	explicit SQLWork(string url,string user,string passwd);
	virtual ~SQLWork();

	int doConnect();
	int changeCharacter(string chars);
	int chooseDatabase(string db);
	int doWork();

	void buildTest();
	void operateTable();
	void operateData();
	void operateDataPre();
	void queryData();
	void queryDataPre();



private:
	string turl;
	string tuser;
	string tpasswd;

	Driver *dirver;
	Connection *con;
	Statement *stmt;
	PreparedStatement *pstmt;
	ResultSet *res;
};

#endif /* SQLWORK_H_ */
