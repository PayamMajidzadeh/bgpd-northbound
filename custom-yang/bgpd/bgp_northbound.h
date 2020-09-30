#ifndef _FRR_BGPD_NB_H_
#define _FRR_BGPD_NB_H_

extern const struct frr_yang_module_info frr_bgpd_info;

/* Mandatory callbacks. */
int bgpd_instance_create(struct nb_cb_create_args *args);
int bgpd_instance_destroy(struct nb_cb_destroy_args *args);
int bgpd_instance_router_id_modify(struct nb_cb_modify_args *args);
int bgpd_instance_router_id_destroy(struct nb_cb_destroy_args *args);
int bgpd_instance_network_create(struct nb_cb_create_args *args);
int bgpd_instance_network_destroy(struct nb_cb_destroy_args *args);
int bgpd_instance_neighbor_create(struct nb_cb_create_args *args);
int bgpd_instance_neighbor_destroy(struct nb_cb_destroy_args *args);


/* Optional 'cli_show' callbacks. */
void bgp_cli_show_header(struct vty *vty, struct lyd_node *dnode,
				  bool show_defaults);
void bgp_cli_show_end_header(struct vty *vty, struct lyd_node *dnode);
void bgp_cli_init(void);



#endif /* _FRR_BGPD_NB_H_ */
