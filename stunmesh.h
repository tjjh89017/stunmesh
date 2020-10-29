#ifndef __STUNMESH_H__
#define __STUNMESH_H__

#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>

struct interface;
struct interface_ops;
struct storage;
struct storage_ops;
struct stun;
struct stun_ops;

struct interface {
	char *name;
	char *type;
	unsigned short listen_port;
	struct sockaddr_in local_endpoint;
	struct sockaddr_in remote_endpoint;
	void *extra_info;
	struct interface_ops *ops;
	struct storage *storage;
	struct stun *stun;
};

struct interface_ops {
	int (*setup_remote_endpoint)(struct interface *iface);
};

struct storage {
	char *name;
	char *type;
	struct storage_ops *ops;
};

struct storage_ops {
	int (*store_local_endpoint)(struct interface *iface);
	int (*get_remote_endpoint)(struct interface *iface);
};

struct stun {
	char *name;
	struct stun_ops *ops;
};

struct stun_ops {
	int (*get_ip_port)(struct interface *iface);
};

#endif
