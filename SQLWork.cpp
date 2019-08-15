/*
 * SQLWork.cpp
 *
 *  Created on: Dec 29, 2016
 *      Author: tla001
 */

#include "SQLWork.h"

SQLWork::SQLWork(string url,string user,string passwd) {
	// TODO Auto-generated constructor stub
	turl=url;
	tuser=user;
	tpasswd=passwd;
}
SQLWork::~SQLWork() {
	// TODO Auto-generated destructor stub
	if(res)
		delete res;
	if(stmt)
		delete stmt;
	if(con)
		delete con;
}

int SQLWork::doConnect(){
	try{
		dirver = get_driver_instance();  //连接数据库
		con = dirver->connect(turl, tuser, tpasswd);
		con->setClientOption("characterSetResults", "utf8");
	}catch(SQLException &e){
		cout << "ERROR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << ")" << endl;

		if (e.getErrorCode() == 1047) {
			/*
			Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
			Message: Unknown command
			*/
			cout << "\nYour server does not seem to support Prepared Statements at all. ";
			cout << "Perhaps MYSQL < 4.1?" << endl;
		}

		return EXIT_FAILURE;
	} catch (runtime_error &e) {
		cout << "ERROR: " << e.what() << endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
int SQLWork::changeCharacter(string chars){
	try{
		con->setClientOption("characterSetResults", chars);
	}catch(SQLException &e){
		cout << "ERROR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << ")" << endl;

		if (e.getErrorCode() == 1047) {
			/*
			Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
			Message: Unknown command
			*/
			cout << "\nYour server does not seem to support Prepared Statements at all. ";
			cout << "Perhaps MYSQL < 4.1?" << endl;
		}

		return EXIT_FAILURE;
	} catch (runtime_error &e) {
		cout << "ERROR: " << e.what() << endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
int SQLWork::chooseDatabase(string db){
	try{
		con->setSchema(db);
		stmt = con->createStatement();  //从表中获取所有信息
	}catch(SQLException &e){
		cout << "ERROR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << ")" << endl;

		if (e.getErrorCode() == 1047) {
			/*
			Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
			Message: Unknown command
			*/
			cout << "\nYour server does not seem to support Prepared Statements at all. ";
			cout << "Perhaps MYSQL < 4.1?" << endl;
		}

		return EXIT_FAILURE;
	} catch (runtime_error &e) {
		cout << "ERROR: " << e.what() << endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int SQLWork::doWork(){
	try{
		/*
		 * 执行具体工作
		 */
		//buildTest();
		//operateTable();
		//operateData();
		//operateDataPre();
		//queryData();
		queryDataPre();

	}catch(SQLException &e){
		cout << "ERROR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << ")" << endl;

		if (e.getErrorCode() == 1047) {
			/*
			Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
			Message: Unknown command
			*/
			cout << "\nYour server does not seem to support Prepared Statements at all. ";
			cout << "Perhaps MYSQL < 4.1?" << endl;
		}

		return EXIT_FAILURE;
	} catch (runtime_error &e) {
		cout << "ERROR: " << e.what() << endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void SQLWork::buildTest(){
	res = stmt->executeQuery("SELECT * from student");  //循环遍历
	while (res->next())  {   //输出，id，name，age字段的信息
		cout << res->getInt("id")
			<< " | " << res->getString(2)
			<< " | " << res->getInt("tage")
			<< " | " << res->getString("thome")
			<< endl;
	}  //清理
}

/*
 * 执行DDL语句Data Definition Language 数据定义语言
 */
void SQLWork::operateTable(){
	//string sqlOp="create table contact(id int primary key auto_increment,name varchar(20),gender varchar(2))";
	//string sqlOp="drop table contact";
	//string sqlOp="ALTER TABLE contact ADD  home VARCHAR(30)";
	//string sqlOp="ALTER TABLE contact drop  home";
	//string sqlOp="ALTER TABLE contact MODIFY gender VARCHAR(4)";
	//string sqlOp="ALTER TABLE contact CHANGE thome home VARCHAR(20);";
	string sqlOp="CREATE TABLE longtest(id INT PRIMARY KEY AUTO_INCREMENT,content LONGTEXT,img LONGBLOB)";

	int count=stmt->executeUpdate(sqlOp);
	cout<<"count "<<count<<endl;
}

/*
 * DML（Data Manipulation Language 数据操控语言）
 */
void SQLWork::operateData(){
	//string sqlOp="INSERT INTO contact VALUES(2,'李','男','shenyang')";
	//string sqlOp="insert contact(name,gender) values('王二丫','女')";
	//string sqlOp="DELETE FROM contact WHERE id>2 and id<5";
	string sqlOp="UPDATE contact SET name='韩' WHERE id=2;";
	//string sqlOp="";
	//string sqlOp="";

	int count=stmt->executeUpdate(sqlOp);
	cout<<"count "<<count<<endl;
}
void SQLWork::operateDataPre(){
	//预编译插入
//	string sqlOp="insert contact(name,gender) values(?,?)";
//	pstmt=con->prepareStatement(sqlOp);
//	pstmt->setString(1,"李四");
//	pstmt->setString(2,"男");

	//预编译修改
//	string sqlOp="UPDATE contact SET name=? WHERE id=?";
//	pstmt=con->prepareStatement(sqlOp);
//	pstmt->setString(1,"王二");
//	pstmt->setInt(2,1);

	//预编译删除
//	string sqlOp="DELETE FROM contact WHERE id>?";
//	pstmt=con->prepareStatement(sqlOp);
//	pstmt->setInt(1,4);

//	int count=pstmt->executeUpdate();
//	cout<<"count "<<count<<endl;


/***********************文本数据*****************************************/
	//保存大文本数据（longtext）
//	string sqlOp="insert longtest(content) values(?)";
//	pstmt=con->prepareStatement(sqlOp);
//	ifstream file;
//	file.open("./file.txt");
//	if(!file){
//		cout<<"open failed"<<endl;
//		exit(-1);
//	}
//	pstmt->setBlob(1,&file);
//
//	int count=pstmt->executeUpdate();
//	cout<<"count "<<count<<endl;
//	file.close();

/***********************二进制数据*****************************************/
	//保存二进制数据（longblob）
	string sqlOp="insert longtest(img) values(?)";
	pstmt=con->prepareStatement(sqlOp);
	ifstream file;
	file.open("./test.png",ios::binary);
	if(!file){
		cout<<"open failed"<<endl;
		exit(-1);
	}
	pstmt->setBlob(1,&file);

	int count=pstmt->executeUpdate();
	cout<<"count "<<count<<endl;
	file.close();
}
/*
 * 数据查询语句DQL
 */
void SQLWork::queryData(){
	string sqlOp="SELECT * FROM contact";
	//string sqlOp="";
	//string sqlOp="";

	res = stmt->executeQuery(sqlOp);  //循环遍历
		while (res->next())  {
			int id=res->getInt("id");
			string name=res->getString("name");
			string gender=res->getString("gender");
			string home=res->getString("home");
			cout<<"id: "<<id<<"\t| name: "<<name<<"\t| gender: "<<gender<<"\t| home: "<<home<<endl;
		}
}

void SQLWork::queryDataPre(){
	//预编译查询
//	string sqlOp="SELECT * FROM contact";
//	//string sqlOp="";
//	//string sqlOp="";
//	pstmt=con->prepareStatement(sqlOp);
//	res = pstmt->executeQuery();
//		while (res->next())  {
//			int id=res->getInt("id");
//			string name=res->getString("name");
//			string gender=res->getString("gender");
//			string home=res->getString("home");
//			cout<<"id: "<<id<<"\t| name: "<<name<<"\t| gender: "<<gender<<"\t| home: "<<home<<endl;
//		}

/***********************文本数据*****************************************/
	//查询大文件数据
//	string sqlOp="SELECT * FROM longtest";
//
//	pstmt=con->prepareStatement(sqlOp);
//	res = pstmt->executeQuery();
//	while (res->next())  {
//		string content=res->getString("content");
//		cout<<content<<endl;
//	}
/***********************二进制数据*****************************************/
	//查询二进制数据
	string sqlOp="SELECT * FROM longtest";

	pstmt=con->prepareStatement(sqlOp);
	res = pstmt->executeQuery();
	int i=0;
	while (res->next())  {
		i++;
		ostringstream iname;
		iname <<"img"<<i<<".png";
		istream *is=res->getBlob("img");
		if(is->peek()>0){
			ofstream file(iname.str().c_str(),ios::binary);
			char data[1024];
			while(is->read(data,1024)){
				file.write(data,sizeof(data));
			}
			file.write(data,sizeof(data));
			file.close();
		}
	}
}
