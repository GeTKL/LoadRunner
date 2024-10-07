Action()
{
	lr_start_transaction("UC02_search_tickets");
	lr_start_transaction("open_webtours");
	
	web_websocket_send("ID=2", 
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1727734884245\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);

	/*Connection ID 2 received buffer WebSocketReceive0*/
	
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

	lr_end_transaction("open_webtours",LR_AUTO);
	lr_think_time(8);
	lr_start_transaction("login");
	
	web_reg_find("Text=Welcome, <b>{login}</b>",LAST);

	web_add_header("Origin", 
		"http://localhost:1080");

	web_submit_form("login.pl", 
		"Snapshot=t2.inf", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		LAST);

	lr_end_transaction("login",LR_AUTO);
	lr_think_time(12);
	lr_start_transaction("click_flights_page");
	
	web_reg_find("Text=<td align\=\"left\">Departure City :</td> <td>", LAST);
	web_reg_save_param_ex("ParamName=Town","LB=\">","RB=\</option>","Ordinal=All",LAST);
	web_reg_save_param_ex("ParamName=Pref","LB=\seatPref\" value\=\"","RB=\"","Ordinal=All",LAST);
	web_reg_save_param_ex("ParamName=Type","LB=\seatType\" value\=\"","RB=\"","Ordinal=All",LAST);

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_image("Search Flights Button", 
		"Alt=Search Flights Button", 
		"Snapshot=t3.inf", 
		LAST);

	lr_end_transaction("click_flights_page",LR_AUTO);
	lr_think_time(8);
	lr_start_transaction("search_flight");
	
	lr_save_string(lr_paramarr_random("Town"), "departCity");
	do{
		lr_save_string(lr_paramarr_random("Town"),"arriveCity");
	} while (strcmp(lr_eval_string("{departCity}"), lr_eval_string("{arriveCity}"))==0);
	
	lr_save_string(lr_paramarr_random("Pref"),"setSeatPref");
	lr_save_string(lr_paramarr_random("Type"),"setSeatType");
	
	web_reg_find("Text=Flight departing from <B>{departCity}</B> to <B>{arriveCity}</B> on <B>{departDate_2}</B>",LAST);

	web_add_header("Origin", 
		"http://localhost:1080");

	web_submit_form("reservations.pl", 
		"Snapshot=t4.inf", 
		ITEMDATA, 
		"Name=depart", "Value={departCity}", ENDITEM, 
		"Name=departDate", "Value={departDate_2}", ENDITEM, 
		"Name=arrive", "Value={arriveCity}", ENDITEM, 
		"Name=returnDate", "Value={returnDate_2}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=roundtrip", "Value=<OFF>", ENDITEM, 
		"Name=seatPref", "Value={setSeatPref}", ENDITEM, 
		"Name=seatType", "Value={setSeatType}", ENDITEM,
		"Name=findFlights.x", "Value=39", ENDITEM,
		"Name=findFlights.y", "Value=11", ENDITEM,		
		LAST);

	lr_end_transaction("search_flight",LR_AUTO);
	lr_think_time(4);
	lr_start_transaction("logout");
	
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);

	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t5.inf", 
		LAST);
	
	lr_end_transaction("logout",LR_AUTO);
	lr_end_transaction("UC02_search_tickets",LR_AUTO);

	return 0;
}