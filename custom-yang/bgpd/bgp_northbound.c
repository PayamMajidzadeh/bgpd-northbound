#include <zebra.h>

#include "command.h"
#include "lib/log.h"
#include "lib/northbound.h"
#include "lib/vrf.h"
#include "libfrr.h"
#include "prefix.h"
#include "table.h"

#include "bgp_northbound.h"
#include "bgpd/bgpd.h"
#include "bgpd/bgp_addpath.h"
#include "bgpd/bgp_aspath.h"
#include "bgpd/bgp_debug.h"
#include "bgpd/bgp_network.h"
#include "bgpd/bgp_nexthop.h"


/*
 * XPath: /frr-bgpd:bgpd/instance
 */

  int bgpd_instance_create(struct nb_cb_create_args * args) {

    static struct bgp *bgp;
    uint32_t asn;
    const char *vrf;
    enum bgp_instance_type inst_type = BGP_INSTANCE_TYPE_DEFAULT;

    switch (args->event) {
    case NB_EV_VALIDATE:
      /* NOTHING */
      break;
    case NB_EV_PREPARE:
      vrf = yang_dnode_get_string(args->dnode, "./vrf");

      asn = yang_dnode_get_uint32(args->dnode, "./asn");
      if (strlen(vrf) > 0)
        inst_type = BGP_INSTANCE_TYPE_VRF;
      
      bgp_get(&bgp, &asn, vrf, inst_type);
      args->resource->ptr = bgp;
      break;
    case NB_EV_ABORT:
      bgp_delete(args->resource->ptr);
      break;
    case NB_EV_APPLY:
      nb_running_set_entry(args->dnode, args->resource->ptr);
      break;
    }

    return NB_OK;
  }

  int bgpd_instance_destroy(struct nb_cb_destroy_args * args) {
    switch (args->event) {
    case NB_EV_VALIDATE:
    case NB_EV_PREPARE:
    case NB_EV_ABORT:
      // /* NOTHING */
      // break;
    case NB_EV_APPLY:
      // bgp = nb_running_unset_entry(args->dnode);
      // bgp_delete(bgp);
      break;
    }

    return NB_OK;
  }

  /*
   * XPath: /frr-bgpd:bgpd/instance/router-id
   */
  int bgpd_instance_router_id_modify(struct nb_cb_modify_args * args) {
    switch (args->event) {
    case NB_EV_VALIDATE:
    case NB_EV_PREPARE:
    case NB_EV_ABORT:
    case NB_EV_APPLY:
      /* TODO: implement me. */
      break;
    }

    return NB_OK;
  }

  int bgpd_instance_router_id_destroy(struct nb_cb_destroy_args * args) {
    switch (args->event) {
    case NB_EV_VALIDATE:
    case NB_EV_PREPARE:
    case NB_EV_ABORT:
    case NB_EV_APPLY:
      /* TODO: implement me. */
      break;
    }

    return NB_OK;
  }

  /*
   * XPath: /frr-bgpd:bgpd/instance/network
   */
  int bgpd_instance_network_create(struct nb_cb_create_args * args) {
    switch (args->event) {
    case NB_EV_VALIDATE:
    case NB_EV_PREPARE:
    case NB_EV_ABORT:
    case NB_EV_APPLY:
      /* TODO: implement me. */
      break;
    }

    return NB_OK;
  }

  int bgpd_instance_network_destroy(struct nb_cb_destroy_args * args) {
    switch (args->event) {
    case NB_EV_VALIDATE:
    case NB_EV_PREPARE:
    case NB_EV_ABORT:
    case NB_EV_APPLY:
      /* TODO: implement me. */
      break;
    }

    return NB_OK;
  }

  /*
   * XPath: /frr-bgpd:bgpd/instance/neighbor
   */
  int bgpd_instance_neighbor_create(struct nb_cb_create_args * args) {
    switch (args->event) {
    case NB_EV_VALIDATE:
    case NB_EV_PREPARE:
    case NB_EV_ABORT:
    case NB_EV_APPLY:
      /* TODO: implement me. */
      break;
    }

    return NB_OK;
  }

  int bgpd_instance_neighbor_destroy(struct nb_cb_destroy_args * args) {
    switch (args->event) {
    case NB_EV_VALIDATE:
    case NB_EV_PREPARE:
    case NB_EV_ABORT:
    case NB_EV_APPLY:
      /* TODO: implement me. */
      break;
    }

    return NB_OK;
  }

  /* clang-format off */
const struct frr_yang_module_info frr_bgpd_info = {
        .name = "frr-bgpd",
        .nodes = {
                {
                        .xpath = "/frr-bgpd:bgpd/instance",
                        .cbs = {
                                .create = bgpd_instance_create,
                                .destroy = bgpd_instance_destroy,
                                // .cli_show = bgp_cli_show_header,
				                        // .cli_show_end = bgp_cli_show_end_header,
                        }
                },
                {
                        .xpath = "/frr-bgpd:bgpd/instance/router-id",
                        .cbs = {
                                .modify = bgpd_instance_router_id_modify,
                                .destroy = bgpd_instance_router_id_destroy,
                        }
                },
                {
                        .xpath = "/frr-bgpd:bgpd/instance/network",
                        .cbs = {
                                .create = bgpd_instance_network_create,
                                .destroy = bgpd_instance_network_destroy,
                        }
                },
                {
                        .xpath = "/frr-bgpd:bgpd/instance/neighbor",
                        .cbs = {
                                .create = bgpd_instance_neighbor_create,
                                .destroy = bgpd_instance_neighbor_destroy,
                        }
                },
                {
                        .xpath = NULL,
                },
        }
};

