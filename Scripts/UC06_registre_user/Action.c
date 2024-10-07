Action()
{

	int i;
	
	lr_start_transaction("UC06_registre_user");
	lr_start_transaction("open_webtours");

	web_reg_find("Text=Welcome to the Web Tours site.",LAST);
	
	web_set_sockets_option("SSL_VERSION", "AUTO");
	web_add_auto_header("Priority", 
		"u=4");
	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		LAST);

	web_websocket_send("ID=1", 
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1728054099521\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);

	/*Connection ID 1 received buffer WebSocketReceive0*/

	lr_end_transaction("open_webtours",LR_AUTO);
	lr_think_time(4);
	lr_start_transaction("open_reg_page");

	web_reg_find("Text=First time registering? Please complete the form below.",LAST);
	
	web_url("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/home.html", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("open_reg_page",LR_AUTO);
	lr_start_transaction("reg_user");

	//regRandomUser
	
	lr_param_sprintf("randomLogin", "%s", lr_eval_string("{randomLetter}"));
	lr_param_sprintf("randomPass", "%s", lr_eval_string("{randomLetter}"));
	for(i = 0; i < atoi(lr_eval_string("{randomDigits}")); i++)
	{
		lr_param_sprintf("randomLogin", "%s%s", lr_eval_string("{randomLogin}"), lr_eval_string("{randomLetter}"));
		lr_param_sprintf("randomPass", "%s%s", lr_eval_string("{randomPass}"), lr_eval_string("{randomLetter}"));
	}
	
	web_reg_find("Text=Thank you, <b>{randomLogin}</b>, for registering and welcome to the Web Tours family",LAST);
	
	web_add_header("Origin", 
		"http://localhost:1080");

	web_submit_data("login.pl_2", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={randomLogin}", ENDITEM, 
		"Name=password", "Value={randomPass}", ENDITEM, 
		"Name=passwordConfirm", "Value={randomPass}", ENDITEM, 
		"Name=firstName", "Value=", ENDITEM, 
		"Name=lastName", "Value=", ENDITEM, 
		"Name=address1", "Value=", ENDITEM, 
		"Name=address2", "Value=", ENDITEM, 
		"Name=register.x", "Value=54", ENDITEM, 
		"Name=register.y", "Value=16", ENDITEM, 
		LAST);

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_url("button_next.gif", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("reg_user",LR_AUTO);
	lr_think_time(6);
	lr_start_transaction("logout");
	
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t12.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);
	lr_end_transaction("UC06_registre_user",LR_AUTO);

	return 0;
}