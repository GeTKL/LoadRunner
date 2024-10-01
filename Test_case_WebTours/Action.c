Action()
{

	lr_start_transaction("T1_buyTicket");
	lr_start_transaction("01_OpenWebTours");
	
	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_auto_header("Priority", 
		"u=0, i");

	web_add_auto_header("DNT", 
		"1");

	web_add_auto_header("Sec-GPC", 
		"1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	
	web_reg_find("Text=Welcome to the Web Tours site.", LAST);

	web_url("webtours", 
		"URL=http://localhost:1080/webtours/", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("01_OpenWebTours", LR_AUTO);
	lr_start_transaction("02_Login");


	web_websocket_send("ID=1", 
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1727557031270\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);

	/*Connection ID 1 received buffer WebSocketReceive0*/

	web_add_auto_header("Priority", 
		"u=4");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(10);
	
	web_reg_find("Text=Welcome, \<b>{login}\</b>, to the Web Tours reservation pages.", LAST);

	web_submit_form("login.pl", 
		"Snapshot=t2.inf", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		LAST);
	
	lr_end_transaction("02_Login", LR_AUTO);
	lr_start_transaction("03_OpenFlights");

	web_reg_find("Text=\<td align\=\"left\"\>Departure City :\</td>",LAST);

	web_reg_save_param_ex("ParamName=Town","LB=\<option value\=\"","RB=\">","Ordinal=All",LAST);
	web_reg_save_param_ex("ParamName=Pref","LB=seatPref\" value\=\"", "RB=\"", "Ordinal=All",LAST);
	web_reg_save_param_ex("ParamName=Type","LB=seatType\" value\=\"", "RB=\"", "Ordinal=All",LAST);
	
	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_image("Search Flights Button", 
		"Alt=Search Flights Button", 
		"Snapshot=t3.inf", 
		LAST);
	
	lr_end_transaction("03_OpenFlights", LR_AUTO);
	lr_start_transaction("04_SearchFlights");
		
	web_add_auto_header("Origin", 
		"http://localhost:1080");

	lr_think_time(7);
	
	web_reg_save_param_ex("ParamName=outboundFlight","LB=outboundFlight\" value\=\"", "RB=\"", "Ordinal=All", LAST);
	
	lr_save_string(lr_paramarr_random("Town"),"departCity");
	do{
	lr_save_string(lr_paramarr_random("Town"),"arriveCity");
	} while (strcmp(lr_eval_string("{departCity}"),lr_eval_string("{arriveCity}"))==0);	
	
	lr_save_string(lr_paramarr_random("Pref"), "pref");
	               
	lr_save_string(lr_paramarr_random("Type"), "type");
	
	web_reg_find("Text=Flight departing from <B>{departCity}</B> to <B>{arriveCity}</B> on <B>{departDate_2}</B>",LAST);
		
	web_submit_form("reservations.pl", 
		"Snapshot=t4.inf", 
		ITEMDATA, 
		"Name=depart", "Value={departCity}", ENDITEM, 
		"Name=departDate", "Value={departDate_2}", ENDITEM, 
		"Name=arrive", "Value={arriveCity}", ENDITEM, 
		"Name=returnDate", "Value={returnDate_2}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=roundtrip", "Value=<OFF>", ENDITEM, 
		"Name=seatPref", "Value={pref}", ENDITEM, 
		"Name=seatType", "Value={type}", ENDITEM,
		"Name=findFlights.x", "Value=39", ENDITEM,
		"Name=findFlights.y", "Value=11", ENDITEM,		
		LAST);
	
	lr_end_transaction("04_SearchFlights", LR_AUTO);
	lr_start_transaction("05_SelectFlights");

	web_reg_find("Text=<b>Payment Details</font></b>",LAST);
	
	lr_save_string(lr_paramarr_random("outboundFlight"),"setOutBoundFlight");
	
	web_submit_form("reservations.pl_2",
		"Snapshot=t5.inf",
		ITEMDATA,
		"Name=outboundFlight", "Value={setOutBoundFlight}", ENDITEM,
		"Name=reserveFlights.x", "Value=29", ENDITEM,
		"Name=reserveFlights.y", "Value=7", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=seatPref", "Value={pref}", ENDITEM,
		"Name=seatType", "Value={type}", ENDITEM,
		LAST);
	
	lr_end_transaction("05_SelectFlights", LR_AUTO);
	lr_start_transaction("06_PaymentsFlights");

	web_reg_find("Text=Thank you for booking through Web Tours.",LAST);

	web_revert_auto_header("Origin");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(26);

	web_submit_form("reservations.pl_3", 
		"Snapshot=t6.inf", 
		ITEMDATA, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={street}", ENDITEM, 
		"Name=address2", "Value={city}", ENDITEM, 
		"Name=pass1", "Value={firstName} {lastName}", ENDITEM, 
		"Name=creditCard", "Value={creditCard}", ENDITEM, 
		"Name=expDate", "Value={expDate}", ENDITEM, 
		"Name=saveCC", "Value=<OFF>", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value={pref}", ENDITEM, 
		"Name=seatType", "Value={type}", ENDITEM,
		"Name=buyFlights.x", "Value=46", ENDITEM,
		"Name=buyFlights.y", "Value=11", ENDITEM,	
		LAST);
	
	lr_end_transaction("06_PaymentsFlights", LR_AUTO);
	lr_start_transaction("07_LogOut");

	web_reg_find("Text=Welcome to the Web Tours site.",LAST);

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(7);

	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t7.inf", 
		LAST);

	lr_end_transaction("07_LogOut", LR_AUTO);
	lr_end_transaction("T1_buyTicket", LR_AUTO);

	
	return 0;
}