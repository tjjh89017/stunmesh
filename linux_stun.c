#include <stunmesh.h>
#include <linux_stun.h>

static int linux_stun_init(struct stun *stun)
{
	LOG("Linux stun init\n");
	stun->fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);

	return 0;
}

static int linux_stun_deinit(struct stun *stun)
{
	LOG("Linux stun deinit\n");
	close(stun->fd);

	return 0;
}

static int linux_stun_setup_server(struct stun *stun, char *ip, unsigned short port)
{
	LOG("Linux stun setup server\n");
	stun->stun_server.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &stun->stun_server.sin_addr);
	stun->stun_server.sin_port = htons(port);

	return 0;
}

static int linux_stun_get_ip_port(struct interface *iface)
{
	LOG("Log Linux stun get ip port\n");

	struct stun *stun = iface->stun;
	int fd = stun->fd;
	struct sockaddr_in *stun_server = &(stun->stun_server);
	unsigned short listen_port = iface->listen_port;
	unsigned short stun_server_port = ntohs(stun_server->sin_port);
	unsigned short length = 8 + 20;
	char buffer[256];
	char *ptr = buffer;
	int ret;

	bzero(buffer, sizeof(buffer));

	/* create UDP header */
	*((unsigned short*)ptr) = htons(listen_port);
	*((unsigned short*)ptr + 1) = htons(stun_server_port);
	*((unsigned short*)ptr + 2) = htons(length);
	*((unsigned short*)ptr + 3) = htons(0);

	/* create stun */
	ptr = ptr + 8;
	/* 
	 * stun method (2 bytes)
	 * msg_length (2 bytes)
	 * magic cookie (4 bytes)
	 * transacation id (12 bytes)
	 *
	 * TODO transcation id need to be random
	 */
	*((unsigned short*)ptr) = htons(0x0001);
	*((unsigned short*)ptr + 1) = htons(0x0000);
	*((uint32_t*)ptr + 1) = htonl(0x2112A442);
	*((uint32_t*)ptr + 2) = htonl(0xdeadbeef);
	*((uint32_t*)ptr + 3) = htonl(0xdeadbeef);
	*((uint32_t*)ptr + 4) = htonl(0xdeadbeef);

	ret = sendto(fd, buffer, length, 0, (struct sockaddr*)stun_server, sizeof(struct sockaddr_in));
	if (ret == -1) {
		LOG("Failed to sendto\n");
	}

	return 0;
}

struct stun_ops linux_stun_ops = {
	.init = linux_stun_init,
	.deinit = linux_stun_deinit,
	.setup_server = linux_stun_setup_server,
	.get_ip_port = linux_stun_get_ip_port
};

/* TODO i don't need linux_stun, i should create stun instance in main() */
struct stun linux_stun = {
	.name = "Linux STUN",
	.fd = -1,
	.ops = &linux_stun_ops
};
