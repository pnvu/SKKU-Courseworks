#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void bin(unsigned n)
{
	/* step 1 */
	if (n > 1)
		bin(n/2);

	/* step 2 */
	printf("%d", n % 2);
}

int main() {

	char ip4_addr[15] = "192.168.1.2";
	printf("IPv4 address: %s\n", ip4_addr);
	unsigned int a = inet_addr(ip4_addr);
	printf("Decimal form: %d\n", a);
	printf("Binary form: \n");
	bin(a);

	printf("\n\nConvert from binary to dot notation form: \n");

	struct sockaddr_in server_address;
	server_address.sin_addr.s_addr = a;	// 127.0.0.1 in our case

	printf("%s\n", inet_ntoa(server_address.sin_addr));

	return 0;
}
