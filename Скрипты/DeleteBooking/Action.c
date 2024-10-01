Action()
{
	int i;

	lr_start_transaction("UC_05_DeleteBooking");
	lr_start_transaction("open_WebTours");
	
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);

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

	web_websocket_send("ID=1", 
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1727734884245\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);

	/*Connection ID 1 received buffer WebSocketReceive0*/

	lr_end_transaction("open_WebTours",LR_AUTO);
	lr_start_transaction("login");
	
	web_reg_find("Text=Welcome, <b>jojo</b>",LAST);

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(9);

	web_submit_form("login.pl", 
		"Snapshot=t2.inf", 
		ITEMDATA, 
		"Name=username", "Value=jojo", ENDITEM, 
		"Name=password", "Value=bean", ENDITEM, 
		LAST);

	lr_end_transaction("login",LR_AUTO);
	lr_think_time(6);
	lr_start_transaction("open_bookingPages");
	
	web_reg_find("Text=<title>Flights List</title>\n",LAST);
	web_reg_save_param_ex("ParamName=saveFlightID","LB=flightID\" value\=\"","RB=\"","Ordinal=All",LAST);
	web_reg_save_param_ex("ParamName=saveCgifields","LB=cgifields\" value\=\"","RB=\"","Ordinal=All",LAST);

	web_image("Itinerary Button", 
		"Alt=Itinerary Button", 
		"Snapshot=t3.inf", 
		LAST);

	lr_end_transaction("open_bookingPages",LR_AUTO);
	lr_start_transaction("deleteBooking");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(18);
	
	lr_save_string(lr_paramarr_random("saveFlightID"),"randomFlightID");
	lr_param_sprintf("c_buffer", "%s=on&", lr_eval_string("{randomFlightID}"));
	
	for (i=1;i<=atoi(lr_eval_string("{saveFlightID_count}"));i++)
    {
        lr_param_sprintf("c_buffer",
        "%sflightID=%s&",
        lr_eval_string("{c_buffer}"),
        lr_paramarr_idx("saveFlightID",
        i));

        lr_param_sprintf("c_buffer",
        "%s.cgifields=%s&",
        lr_eval_string("{c_buffer}"),
        lr_paramarr_idx("saveCgifields",
        i));
    }
	
	lr_save_string(lr_eval_string("{c_buffer}removeFlights.x=12&removeFlights.y=7"), "c_wcr");

    lr_save_string(lr_eval_string(lr_eval_string("{randomFlightID}")),"c_cancelflight");
	
	web_custom_request("itinerary.pl_2",
    "URL=http://localhost:1080/cgi-bin/itinerary.pl",
    "Method=POST",
    "Resource=0",
    "RecContentType=text/html",
    "Referer=http://localhost:1080/cgi-bin/itinerary.pl",
    "Snapshot=t23.inf",
    "Mode=HTTP",
    "Body={c_wcr}",
    LAST);

	lr_end_transaction("deleteBooking",LR_AUTO);
	lr_think_time(10);
	lr_start_transaction("logout");

	web_reg_find("Text=Welcome to the Web Tours site.",LAST);
	
	web_url("welcome.pl_2", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);
	lr_end_transaction("UC_05_DeleteBooking",LR_AUTO);

	return 0;
}