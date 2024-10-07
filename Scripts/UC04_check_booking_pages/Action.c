Action()
{
	lr_start_transaction("UC04_check_booking_pages");
	lr_start_transaction("open_webtours");
	
	web_websocket_send("ID=0", 
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1727734884245\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);

	/*Connection ID 0 received buffer WebSocketReceive0*/
	
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);

	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_auto_header("Priority", 
		"u=0, i");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("open_webtours",LR_AUTO);
	lr_think_time(6);
	lr_start_transaction("login");

	web_reg_find("Text=Welcome, <b>{login}</b>",LAST);
	
	web_add_auto_header("Priority", 
		"u=4");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_submit_form("login.pl", 
		"Snapshot=t2.inf", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		LAST);

	lr_end_transaction("login",LR_AUTO);
	lr_think_time(9);
	lr_start_transaction("open_booking_pages");
	
	web_reg_find("Text=<title>Flights List</title>\n",LAST);

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_image("Itinerary Button", 
		"Alt=Itinerary Button", 
		"Snapshot=t3.inf", 
		LAST);

	lr_end_transaction("open_booking_pages",LR_AUTO);
	lr_think_time(4);
	lr_start_transaction("logout");
	
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);

	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t4.inf", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);
	lr_end_transaction("UC04_check_booking_pages",LR_AUTO);

	return 0;
}