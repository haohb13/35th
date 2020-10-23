 ///
 /// @file    TcpConnection.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-07 16:44:49
 ///
 
#ifndef __WD_TCPCONNECTION_H__
#define __WD_TCPCONNECTION_H__

#include "Socket.h"
#include "InetAddress.h"
#include "SocketIO.h"
#include "Noncopyable.h"

#include <string>
#include <memory>
#include <functional>
using std::string;

namespace wd
{

class TcpConnection;
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void(const TcpConnectionPtr & conn)>;

class TcpConnection
: Noncopyable
, public std::enable_shared_from_this<TcpConnection>
{
public:
	TcpConnection(int fd);
	~TcpConnection();

	string receive();
	void send(const string & msg);

	string toString() const;
	void shutdown();

	void setConnectionCallback(const TcpConnectionCallback & cb);
	void setMessageCallback(const TcpConnectionCallback & cb);
	void setCloseCallback(const TcpConnectionCallback & cb);

	void handleConnectionCallback();
	void handleMessageCallback();
	void handleCloseCallback();

	bool isConnectionClose();

private:
	InetAddress getLocalAddr(int fd);
	InetAddress getPeerAddr(int fd);
private:
	Socket _sock;
	SocketIO _socketIo;
	InetAddress _localAddr;
	InetAddress _peerAddr;
	bool _isShutdwonWrite;

	TcpConnectionCallback _onConnection;
	TcpConnectionCallback _onMessage;
	TcpConnectionCallback _onClose;
};

}//end of namespace wd

#endif
