
#include <zebra.h>

#include "lib/command.h"
#include "lib/log.h"
#include "lib/northbound_cli.h"
#include "if.h"
#include "vrf.h"
#include "log.h"
#include "prefix.h"
#include "command.h"
#include "northbound_cli.h"
#include "libfrr.h"

#include "bgpd/bgpd.h"
#include "bgpd/bgp_northbound.h"

#ifndef VTYSH_EXTRACT_PL
#include "bgpd/bgp_cli_clippy.c"
#endif /* VTYSH_EXTRACT_PL */


/*
 * XPath: /frr-bgpd:bgpd/instance
 */
DEFPY_NOSH(
	router_bgp,
	router_bgp_cmd,
	"router bgp (1-4294967295)$as [vrf NAME]",
	ROUTER_STR
	BGP_STR
	AS_STR
	VRF_CMD_HELP_STR)
{
	char xpath[XPATH_MAXLEN];
	int rv;

	/* Build BGP instance XPath. */
	snprintf(xpath, sizeof(xpath),
		 "/frr-bgpd:bgpd/instance[asn='%s'][vrf='%s']",
		 as_str, vrf ? vrf : VRF_DEFAULT_NAME);

	nb_cli_enqueue_change(vty, xpath, NB_OP_CREATE, NULL);
	rv = nb_cli_apply_changes(vty, NULL);
	if (rv == CMD_SUCCESS)
		VTY_PUSH_XPATH(BGP_NODE, xpath);

	return rv;
}

DEFPY(
	no_router_bgp,
	no_router_bgp_cmd,
	"no router bgp (1-4294967295)$as [vrf NAME]",
	NO_STR
	ROUTER_STR
	BGP_STR
	AS_STR
	VRF_CMD_HELP_STR)
{
	char xpath[XPATH_MAXLEN];

	snprintf(xpath, sizeof(xpath),
		 "/frr-bgpd:bgpd/instance[asn='%s'][vrf='%s']",
		 as_str, vrf ? vrf : VRF_DEFAULT_NAME);

	nb_cli_enqueue_change(vty, xpath, NB_OP_DESTROY, NULL);
	return nb_cli_apply_changes(vty, NULL);
}

void bgp_cli_show_header(struct vty *vty, struct lyd_node *dnode,
			   bool show_defaults)
{
	const char *asn = yang_dnode_get_string(dnode, "./asn");
	const char *vrf = yang_dnode_get_string(dnode, "./vrf");

	vty_out(vty, "router bgp %s", asn);
	if (strcmp(vrf, VRF_DEFAULT_NAME))
		vty_out(vty, " vrf %s", vrf);
	vty_out(vty, "\n");
}

void bgp_cli_show_end_header(struct vty *vty, struct lyd_node *dnode)
{
	vty_out(vty, "!\n");
}



/*
 * CLI installation procedures.
 */
int bgp_config_write(struct vty *vty);
static struct cmd_node bgp_node = {
	.name = "bgp",
	.node = BGP_NODE,
	.parent_node = CONFIG_NODE,
	.prompt = "%s(config-router)# ",
	.config_write = bgp_config_write,
};

int bgp_config_write(struct vty *vty)
{
	struct lyd_node *dnode;
	int written = 0;

	dnode = yang_dnode_get(running_config->dnode, "/frr-bgpd:bgpd");
	if (dnode) {
		nb_cli_show_dnode_cmds(vty, dnode, false);
		written = 1;
	}

	return written;
}



void bgp_cli_init(void)
{
	install_element(CONFIG_NODE, &router_bgp_cmd);
	install_element(CONFIG_NODE, &no_router_bgp_cmd);

	install_node(&bgp_node);
	install_default(BGP_NODE);

	// install_element(BGP_NODE, &bgp_router_id_cmd);
	// install_element(BGP_NODE, &no_bgp_router_id_cmd);
	// install_element(BGP_NODE, &bgp_network_cmd);
	// install_element(BGP_NODE, &bgp_neighbor_cmd);
}
