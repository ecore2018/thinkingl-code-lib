#pragma once

/** ��¼��־. 
*	+by lizhixing@2015-06-04
*/

#include <vector>
#include <string>
#include <sstream>

class CLog
{
public:
	CLog();
	~CLog();

	// ����.
	CLog& newline();

// 	CLog& operator <<(const char* pAnsiStr);
// 	CLog& operator <<( int val );
// 	CLog& operator <<(const wchar_t* pWStr);
// 	CLog& operator <<(void*);	// 16�������.

	/**	һ�����־���, �ַ����Ļ�ֻ֧��UTF-8��. */
	template< typename _T >
	CLog& operator << (_T logItem)
	{
		m_curLine << logItem;
		return *this;
	}

	// ������־�����һ���������ַ���.
	void toString( std::wstring& str );

private:
	// ����־ȫ��������.
	typedef std::vector<std::wstring> CLogList;
	CLogList m_logList;

	// ������־.
	std::wstringstream  m_curLine;
};

static CLog s_log;

// д��־�����������.
inline CLog& LOG()
{
	return s_log.newline();
}
