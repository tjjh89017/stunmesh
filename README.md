# stunmesh
use STUN to create Full Mesh VPN topology

---

## data struct

interface
- name
- real network interface (to send VPN)
- type (wg, vxlan)
- listen_port
- local_endpoint (current, real)
- remote_endpoint (current)
- interface_additional_attributes (keypair in wg)
- interface_ops (to setup remote endpoint)
- storage (OpenDHT or other hashtable service to store and get remote endpoint)
    - if need to store encrypted endpoint info, need to setup pre-shared key or use wireguard key pair sealbox
- stun (to get real IP and port)

storage
- name
- type
- storage_ops (store, get)

stun
- name
- stun_ops (get_ip_port)
