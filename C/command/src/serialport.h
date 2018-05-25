#ifndef _INCL_SERIALPORT
#define _INCL_SERIALPORT

typedef uint8_t			byte;

enum Parity
{
	parityEnabled,
	parityDisabled
};

enum Duplex
{
	halfDuplex,
	fullDuplex
};

enum StopBits
{
	stopbits1,
	stopbits2
};

enum DataBits
{
	databits5,
	databits6,
	databits7,
	databits8
};

class SerialPort
{
	private:
		SerialPort() {}
		
		int			fd;
		bool		isHalfDuplex = false;
		bool		isConfigured = false;
		
		char		szPortName[256];
		int			baud;
		Parity		parity;
		Duplex		duplex;
		StopBits	stopBits;
		DataBits	dataBits;

		void		setRTS();
		void		clearRTS();
		void		_setPortParams();
		
	public:
		static SerialPort &	getInstance()
		{
			static SerialPort	instance;
			
			return instance;
		}
		
		SerialPort(SerialPort const&)		= delete;
		void operator = (SerialPort const&)	= delete;
		
		void	configure(
					char * pszPortName,
					int baud,
					Parity parity,
					Duplex duplex,
					StopBits stopBits,
					DataBits dataBits);
					
		void	openPort(bool wait);
		void	closePort();
		
		void	tx(byte data);
		byte	rx(void);
		
		void	tx(byte * p, int length);
		int		rx(byte * p, int size, int length);
};

#endif