#include "tcp_server.h"
#include "config.h"
#include "log.h"

namespace aboo {

static aboo::ConfigVar<uint64_t>::ptr g_tcp_server_read_timeout =
	aboo::Config::Lookup("tcp_server.read_timeout", (uint64_t)(60 * 1000 * 2), "tcp server read timeout");

static aboo::Logger::ptr g_logger = ABOO_LOG_NAME("system");

TcpServer::TcpServer(aboo::IOManager* worker, aboo::IOManager* accept_worker)
	: m_worker(worker)
	, m_acceptWorker(accept_worker)
	, m_recvTimeout(g_tcp_server_read_timeout->getValue())
	, m_name("aboo/1.0.0")
	, m_isStop(true) {
}

TcpServer::~TcpServer() {
	for (auto& i : m_socks) {
		i->close();
	}
	m_socks.clear();
}

bool TcpServer::bind(aboo::Address::ptr addr) {
	std::vector<Address::ptr> addrs;
	std::vector<Address::ptr> failed;
	addrs.push_back(addr);
	return bind(addrs, failed);
}

bool TcpServer::bind(const std::vector<Address::ptr>& addrs, std::vector<Address::ptr>& failed) {
	for (auto& addr : addrs) {
		Socket::ptr sock = Socket::CreateTCP(addr);
		if (!sock->bind(addr)) {
			ABOO_LOG_ERROR(g_logger) << "bind fail errno=" << errno
									 << " strerr=" << strerror(errno)
									 << " addr=[" << addr->toString() << "]";
			failed.push_back(addr);
			continue;
		}
		if (!sock->listen()) {
			ABOO_LOG_ERROR(g_logger) << "listen fail errno=" << errno
									 << " strerr=" << strerror(errno)
									 << " addr=[" << addr->toString() << "]";
			failed.push_back(addr);
			continue;
		}
		m_socks.push_back(sock);
	}
	if (!failed.empty()) {
		m_socks.clear();
		return false;
	}

	for (auto& i : m_socks) {
		ABOO_LOG_INFO(g_logger) << "server bind and listen success: " << *i;
	}
	return true;
}

bool TcpServer::start() {
	if (!m_isStop) return true;
	m_isStop = false;
	for (auto& sock : m_socks) {
		m_acceptWorker->schedule(std::bind(&TcpServer::startAccept, shared_from_this(), sock));
	}
	return true;
}

void TcpServer::stop() {
	m_isStop = true;
	auto self = shared_from_this();
	m_acceptWorker->schedule([this, self]() {
		for (auto& sock : m_socks) {
			sock->cancelAll();
			sock->close();
		}
		m_socks.clear();
	});
}

void TcpServer::handleClient(Socket::ptr client) {
	ABOO_LOG_INFO(g_logger) << "handleClient: " << *client;
}

void TcpServer::startAccept(Socket::ptr sock) {
	while (!m_isStop) {
		Socket::ptr client = sock->accept();
		if (client) {
			client->setRecvTimeout(m_recvTimeout);
			m_worker->schedule(std::bind(&TcpServer::handleClient, shared_from_this(), client));
		} else {
			//if (errno == EAGAIN) continue;
			ABOO_LOG_ERROR(g_logger) << "accept errno=" << errno
									 << " strerr=" << strerror(errno);
		}
	}
}

}
