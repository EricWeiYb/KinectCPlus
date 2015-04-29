#include "stdafx.h"
#include "CMysqlProcess.h"


MySqlProcess::MySqlProcess() : m_pRes(NULL),m_bConnected(false),m_errNo(0),m_rowNum(-1),m_fieldNum(-1),m_affectedNum(-1),m_insertID(-1),m_bHaveResult(false)
{
	mysql_init(&m_conn);
}

MySqlProcess::~MySqlProcess()
{
	close();
}

int MySqlProcess::connect(char *hostAddress, int port, char *username, char *password,  char *DBName)
{
#if MYSQL_VERSION_ID > 50012
	mysql_options(&m_conn, MYSQL_OPT_RECONNECT, "1");
#endif
	if (mysql_real_connect(&m_conn, hostAddress, username, password, DBName, port, NULL, 0) == 0)
	{
		sprintf_s(m_errMsg, 256, "Fail To Connect To Mysql: %s", mysql_error(&m_conn));
		my_err(__LINE__);
		return CONNECT_FAILED;
	}

	m_bConnected = true;

	if (strcmp(DBName, "") != 0)
	{
		if (mysql_select_db(&m_conn, DBName) < 0)
		{
			sprintf_s(m_errMsg, 256, "Cannot Select Database %s: %s", DBName, mysql_error(&m_conn));
			my_err(__LINE__);
			return CONNECT_FAILED;
		}
	}
	strncpy_s(m_hostAddress, hostAddress, 64);
	strncpy_s(m_username, username, 64);
	strncpy_s(m_password, password, 64);
	strncpy_s(m_DBName, DBName, 64);
	m_port = port;

	strncpy_s(m_errMsg, "", 256);
	return 0;
}

int MySqlProcess::reconnect()
{
	close();
	if (strcmp(m_hostAddress, "") == 0)
	{
		sprintf_s(m_errMsg, 256, "host is empty");
		my_err(__LINE__);
		return CONNECT_FAILED;
	}
	return connect(m_hostAddress, m_port, m_username, m_password, m_DBName);
}

int MySqlProcess::close()
{
	if (m_bHaveResult)
	{
		mysql_free_result(m_pRes);
		m_bHaveResult = false;
		m_rowNum = 0;
		m_fieldNum = 0;
		m_affectedNum = 0;
		m_insertID = -1;
	}
	if (m_bConnected)
	{
		mysql_close(&m_conn);
		m_bConnected = false;
	}
	return 0;
}

int MySqlProcess::exec(char *pSql)
{
	if (m_bHaveResult)
	{
		mysql_free_result(m_pRes);
		m_bHaveResult = false;
		m_rowNum = 0;
		m_fieldNum = 0;
		m_affectedNum = 0;
		m_insertID = -1;
	}
	if (!m_bConnected)
	{
		reconnect();
		if (!m_bConnected)
		{
			strncpy_s(m_errMsg, "Has Not Connect To DB Server Yet", 256);
			my_err(__LINE__);
			return CONNECT_FAILED;
		}
	}

	int res = mysql_query(&m_conn, pSql);
	if (res != 0)
	{
		reconnect();
		res = mysql_query(&m_conn, pSql);
		if (res != 0)
		{
			m_errNo = mysql_errno(&m_conn);
			char err_sql[200];
			memset(err_sql, 0, 200);
			strncpy_s(err_sql, pSql, 199);
			sprintf_s(m_errMsg, 256, "Fail To Execute SQL: %s:%d", err_sql, m_errNo);
			my_err(__LINE__);
			return EXECUTE_FAILED;
		}
	}
	m_pRes = mysql_store_result(&m_conn);
	if (m_pRes)
	{
		m_bHaveResult = true;
		m_rowNum = mysql_num_rows(m_pRes);
		m_fieldNum = mysql_num_fields(m_pRes);
	}
	m_affectedNum = mysql_affected_rows(&m_conn);
	m_insertID = mysql_insert_id(&m_conn);
	return 0;
}

int MySqlProcess::real_exec(char *pSql, unsigned int length)
{
	if (m_bHaveResult)
	{
		mysql_free_result(m_pRes);
		m_bHaveResult = false;
		m_rowNum = 0;
		m_fieldNum = 0;
		m_affectedNum = 0;
		m_insertID = -1;
	}
	if (!m_bConnected)
	{
		reconnect();
		if (!m_bConnected)
		{
			strncpy_s(m_errMsg, "Has Not Connect To DB Server Yet", 256);
			my_err(__LINE__);
			return CONNECT_FAILED;
		}
	}

	int res = mysql_real_query(&m_conn, pSql, length);
	if (res != 0)
	{
		reconnect();
		res = mysql_real_query(&m_conn, pSql, length);
		if (res != 0)
		{
			m_errNo = mysql_errno(&m_conn);
			char err_sql[200];
			memset(err_sql, 0, 200);
			strncpy_s(err_sql, pSql, 199);
			sprintf_s(m_errMsg, 256, "Fail To Execute SQL: %s:%d", err_sql, m_errNo);
			my_err(__LINE__);
			return EXECUTE_FAILED;
		}
	}
	m_pRes = mysql_store_result(&m_conn);
	if (m_pRes)
	{
		m_bHaveResult = true;
		m_rowNum = mysql_num_rows(m_pRes);
		m_fieldNum = mysql_num_fields(m_pRes);
	}
	m_affectedNum = mysql_affected_rows(&m_conn);
	m_insertID = mysql_insert_id(&m_conn);
	return 0;
}

int MySqlProcess::exec(const string &sql)
{
	exec((char *)sql.c_str());
	return 0;
}

int MySqlProcess::real_exec(const string &sql, unsigned int length)
{
	real_exec((char *)sql.c_str(), length);
	return 0;
}

int MySqlProcess::fetchrow()
{
	if (!m_bHaveResult)
	{
		sprintf_s(m_errMsg, 256, "Recordset is Null");
		my_err(__LINE__);
		return EMPTY_RECORDSET;
	}

	m_row = mysql_fetch_row(m_pRes);
	return 0;
}

int MySqlProcess::fetchrow(map<string, string> *row)
{
	row->clear();
	if ( fetchrow() == EMPTY_RECORDSET || m_rowNum <= 0) {
		return EMPTY_RECORDSET;
	}
	MYSQL_FIELD *field = mysql_fetch_fields(m_pRes);
	mysql_field_seek(m_pRes, 0);
	string field_name, field_value;
	for (unsigned int i = 0; i< m_fieldNum; ++i)
	{
		field_name = field[i].name;
		field_value = m_row[i] == 0 ? "" : m_row[i];
		(*row)[field_name] = field_value;
	}
	return 0;
}

void MySqlProcess::my_err(int line)
{
	fprintf(stderr, "line:%d %s\n", line, m_errMsg);
}



void MySqlProcess::ReadTxt(const string &path,double *data,int width,int height)
{
	//double a[800][3];
	ifstream file(path);
	//width = 0;
	//height = 0;
	if (file.is_open())
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j< width; ++j)
			{
				file>>data[i * 3 + j];
				//std::cout<<data[i * 3 + j]<<std::endl;
			}	
		}
	}
	file.close();
}