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

	iface.stun->ops->get_ip_port(&iface);
	return 0;
}
