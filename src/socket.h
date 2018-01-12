#ifndef EREBOS_SOCKET_H
#define EREBOS_SOCKET_H

#ifndef _MSC_VER

#include <string>
#include "platform_defs.h"

namespace erebos {

	namespace socket {

		struct HTTPRequest {

			unsigned int version_major {1};
			unsigned int version_minor {1};
			std::string method {"GET"};
			std::string URL {"/"};
			std::string host {""};
			std::string user_agent {"Mozilla/5.0"};
			std::string language {"en-us"};
			std::string encoding {"gzip, deflate"};
			std::string connection {"Keep-Alive"};
			std::string keepalive {"timeout=15"};
			std::string cache {"no-cache"};

			std::string str();

		};

		ERAPI std::string forge_http_packet(HTTPRequest request);

		extern bool initialized;

		ERAPI int initialize();

		ERAPI void destroy();

		class TCPSocket {
			private:
				void* host_entity;
				void* address;
				bool open {false};
			public:

				ERAPI TCPSocket();

				ERAPI ~TCPSocket();

				ERAPI int connect(std::string hostname, unsigned int port);

				ERAPI int read(char** buffer, unsigned int packetsize = 512);

				ERAPI int write(std::string data);

				ERAPI int write(char* data, size_t size);

				ERAPI int close();

		};

	}

}

#endif

#endif
