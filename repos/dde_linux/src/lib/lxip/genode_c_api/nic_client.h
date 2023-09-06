#ifndef __GENODE_C_API__NIC_CLIENT_H_
#define __GENODE_C_API__NIC_CLIENT_H_

#include <genode_c_api/base.h>
#include <genode_c_api/mac_address_reporter.h>

#ifdef __cplusplus
extern "C" {
#endif

void genode_nic_client_init(struct genode_env *,
                            struct genode_allocator *,
                            struct genode_signal_handler *);

void genode_nic_client_notify_peers(void);

struct genode_nic_client;

struct genode_nic_client *genode_nic_client_create(char const *label);
void   genode_nic_client_destroy(struct genode_nic_client *);


struct genode_mac_address genode_nic_client_mac_address(struct genode_nic_client *);

struct genode_nic_client_tx_packet_context;

/**
 * Callback called by 'genode_nic_client_tx_packet' to provide the content
 */
typedef unsigned long (*genode_nic_client_tx_packet_content_t)
	(struct genode_nic_client_tx_packet_context *, char *dst, unsigned long dst_len);

/**
 * Process packet transmission
 *
 * \return true if progress was made
 */
bool genode_nic_client_tx_packet(struct genode_nic_client *,
                                 genode_nic_client_tx_packet_content_t,
                                 struct genode_nic_client_tx_packet_context *);


/*********************************************
 ** Receive packets from the nic_client session **
 *********************************************/

struct genode_nic_client_rx_context;

typedef enum { GENODE_NIC_CLIENT_RX_REJECTED,
               GENODE_NIC_CLIENT_RX_ACCEPTED,
               GENODE_NIC_CLIENT_RX_RETRY } genode_nic_client_rx_result_t;

typedef genode_nic_client_rx_result_t (*genode_nic_client_rx_one_packet_t)
	(struct genode_nic_client_rx_context *, char const *ptr, unsigned long len);

/**
 * Process packet reception
 *
 * \return true if progress was made
 */
bool genode_nic_client_rx(struct genode_nic_client *,
                          genode_nic_client_rx_one_packet_t rx_one_packet,
                          struct genode_nic_client_rx_context *);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __GENODE_C_API__NIC_CLIENT_H_ */
