#include"httpd.h"
#include"http_config.h"
#include"http_protocol.h"
#include"ap_config.h"
// the sample content handler
static int labelmaker_handler(reques_rec *r)
{
	if(strcmp(r->handler,"labelmaker"))
	{
		return 	DECLINED
	}
	r->content_type="text/html";
	if(!r->headler_only)
		ap_rputs("the sample page from mod_labelmaker.c\n",r);
	return ok;
}
static void labelmaker_register_hooks(apr_pool_t *p)
{
	ap_hook_handler(labelmaker_handler,NULL,NULL,APR_HOOK_MIDDLE);
}
//dispatch list for API hooks
module AP_MODULE_DECLARE_DATA labelmaker_module=
{
	STANDARD20_MODULE_STUFF,NULL,NULL,NULL,NULL,NULL,labelmaker_register_hooks
};