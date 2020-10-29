#include <stunmesh.h>

int linux_stun_get_ip_port(struct interface *iface)
{
	puts("Log Linux stun get ip port");
	return 0;
}

struct stun_ops ops = {
	.get_ip_port = linux_stun_get_ip_port
};

struct stun linux_stun = {
	.name = "Linux STUN",
	.ops = &ops
};
