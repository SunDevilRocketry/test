#ifndef STUBS /* recursive inclusion guard */
/* globals */
extern bool was_gps_enabled;

/* functions */
void stubs_reset();
void set_return_ign_deploy_main
	(
	IGN_STATUS new_status[3]
	);
void set_return_ign_deploy_drogue
	(
	IGN_STATUS new_status[3]
	);
unsigned int get_num_calls_ign_deploy_main();
unsigned int get_num_calls_ign_deploy_drogue();
#endif