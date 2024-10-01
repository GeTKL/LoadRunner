Action()
{

	lr_start_transaction("open_WebTours");

	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_auto_header("Priority", 
		"u=4");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	web_websocket_send("ID=2", 
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1727718500963\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);

	/*Connection ID 2 received buffer WebSocketReceive0*/

	lr_end_transaction("open_WebTours",LR_AUTO);

	lr_start_transaction("login");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(18);

	web_submit_form("login.pl", 
		"Snapshot=t2.inf", 
		ITEMDATA, 
		"Name=username", "Value=jojo", ENDITEM, 
		"Name=password", "Value=bean", ENDITEM, 
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_think_time(9);

	lr_start_transaction("logout");

	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t3.inf", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);

	return 0;
}