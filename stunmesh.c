#include <stdlib.h>
#include <stdio.h>

#include <stunmesh.h>
#include <linux_stun.h>

int main(int argc, char* argv[])
{
	struct interface iface = {
		.name = "testing interface",
		.type = "testing type",
		.listen_port = 5566,
		.ops = NULL,
		.storage = NULL,
		.stun = &linux_stun
	};

	iface.stun->ops->init(&linux_stun);
	iface.stun->ops->setup_server(&linux_stun, "51.79.146.53", 3478);
	iface.stun->ops->get_ip_port(&iface);
	iface.stun->ops->deinit(&linux_stun);
	return 0;
}
