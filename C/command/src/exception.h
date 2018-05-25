#include <stdint.h>
#include <string>

#ifndef _INCL_EXCEPTION
#define _INCL_EXCEPTION

#define	ERR_MALLOC					0x00000001
#define ERR_INDEX_OUT_OF_RANGE		0x00000002
#define ERR_ARRAY_OVERFLOW			0x00000004
#define ERR_THREAD_CREATE			0x00000008
#define ERR_INVALID_NUM_ARGUMENTS	0x00000010
#define ERR_IOCTL					0x00000020
#define ERR_TERMIOS					0x00000040
#define ERR_OPEN_PORT				0x00000080
#define ERR_PORT_IO					0x00000100
#define ERR_INVALID_RX_CHAR			0x00000200

#define ERR_UNDEFINED				0x0000FFFF

using namespace std;

class Exception
{
	private:
		uint32_t	errorCode;
		string		message;

		string		fileName;
		string		className;
		string		methodName;

		string 		exception;

		uint32_t	lineNumber;

		void		_initialise();

	public:
					Exception();
					Exception(const string & message);
					Exception(uint32_t errorCode, const string & message);
					Exception(
							uint32_t errorCode,
							const string & message,
							const string & fileName,
							const string & className,
							const string & methodName,
							uint32_t lineNumber);

		uint32_t		getErrorCode();
		uint32_t		getLineNumber();

		string &	getFileName();
		string &	getClassName();
		string &	getMethodName();

		string &	getMessage();

		string &	getExceptionString();
};

#endif
