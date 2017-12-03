#ifndef EREBOS_SOCKET_H
#define EREBOS_SOCKET_H
#include <string>
#include "platform_defs.h"

namespace erebos {

	namespace socket {

		struct HTTPRequest {
			unsigned int version_major {1};
			unsigned int version_minor {1};
			std::string user_agent {""};
		};

		extern bool initialized;

		int initialize();

		void destroy();

		std::string forge_http_packet(HTTPRequest request);

		class Socket {
			protected:
				void* host_entity;
				bool open {false};
			public:

				virtual int connect(std::string hostname, unsigned int port) = 0;

				virtual int read(char* buffer, unsigned int packetsize) = 0;

				virtual int write(std::string data) = 0;

				//int write(std::unique_ptr<char[]> data, size_t size) = 0;

				virtual int close() = 0;

		};


		class TCPSocket : Socket {
			public:

				TCPSocket();

				~TCPSocket();

				int connect(std::string hostname, unsigned int port);

				int read(char* buffer, unsigned int packetsize = 512);

				int write(std::string data);

				//int write(std::unique_ptr<char[]> data, size_t size);

				int close();

		};


		class UDPSocket : Socket {
			public:

				UDPSocket();

				~UDPSocket();

				int connect(std::string hostname, unsigned int port);

				int read(char* buffer, unsigned int packetsize);

				int write(std::string data);

				//int write(std::unique_ptr<char[]> data, size_t size);

				int close();

		};

	}

}

#endif
