Action()
{

	lr_start_transaction("UC_03_BuyTickets");
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

	web_websocket_send("ID=2", 
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1727734884245\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);

	/*Connection ID 2 received buffer WebSocketReceive0*/

	lr_end_transaction("open_WebTours",LR_AUTO);
	lr_start_transaction("login");
	
	web_reg_find("Text=Welcome, <b>{login}</b>",LAST);

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(7);

	web_submit_form("login.pl", 
		"Snapshot=t2.inf", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		LAST);

	lr_end_transaction("login",LR_AUTO);
	lr_think_time(14);
	lr_start_transaction("click_FlightsPage");
	
	web_reg_find("Text=<td align\=\"left\">Departure City :</td> <td>", LAST);
	web_reg_save_param_ex("ParamName=Town","LB=\">","RB=\</option>","Ordinal=All",LAST);
	web_reg_save_param_ex("ParamName=pref","LB=\seatPref\" value\=\"","RB=\"","Ordinal=All",LAST);
	web_reg_save_param_ex("ParamName=type","LB=\seatType\" value\=\"","RB=\"","Ordinal=All",LAST);

	web_image("Search Flights Button", 
		"Alt=Search Flights Button", 
		"Snapshot=t3.inf", 
		LAST);

	lr_end_transaction("click_FlightsPage",LR_AUTO);
	lr_start_transaction("searchFlight");
	
	web_reg_save_param_ex("ParamName=outboundFlight","LB=\outboundFlight\" value\=\"","RB=\"","Ordinal=All",LAST);
	
	lr_save_string(lr_paramarr_random("pref"),"RandomPref");
	lr_save_string(lr_paramarr_random("type"),"RandomType");
	
	lr_save_string(lr_paramarr_random("Town"),"departCity");
	do{
		lr_save_string(lr_paramarr_random("Town"),"arriveCity");
	} while (strcmp(lr_eval_string("{departCity}"),lr_eval_string("{arriveCity}"))==0); //¬ыбор города случайного, чтобы не повтор€лс€
	
	web_reg_find("Text=Flight departing from <B>{departCity}</B> to <B>{arriveCity}</B> on <B>{departDate_2}</B>",LAST);
	
	web_add_auto_header("Origin", 
		"http://localhost:1080");

	lr_think_time(10);

	web_submit_form("reservations.pl", 
		"Snapshot=t4.inf", 
		ITEMDATA, 
		"Name=depart", "Value={departCity}", ENDITEM, 
		"Name=departDate", "Value={departDate_2}", ENDITEM, 
		"Name=arrive", "Value={arriveCity}", ENDITEM, 
		"Name=returnDate", "Value={returnDate_2}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=roundtrip", "Value=<OFF>", ENDITEM, 
		"Name=seatPref", "Value={RandomPref}", ENDITEM, 
		"Name=seatType", "Value={RandomType}", ENDITEM, 
		"Name=findFlights.x", "Value=39", ENDITEM,
		"Name=findFlights.y", "Value=11", ENDITEM,	
		LAST);

	lr_end_transaction("searchFlight",LR_AUTO);
	lr_think_time(13);
	lr_start_transaction("selectPlane");
	
	web_reg_find("Text=<b>Payment Details</font></b>",LAST);
	lr_save_string(lr_paramarr_random("outboundFlight"),"randomOutBoundFlight");

	web_submit_form("reservations.pl_2", 
		"Snapshot=t5.inf", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={randomOutBoundFlight}", ENDITEM, 
		"Name=reserveFlights.x", "Value=46", ENDITEM, 
		"Name=reserveFlights.y", "Value=10", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=seatPref", "Value={RandomPref}", ENDITEM,
		"Name=seatType", "Value={RandomType}", ENDITEM,
		LAST);

	lr_end_transaction("selectPlane",LR_AUTO);
	lr_think_time(15);
	lr_start_transaction("PaymentsForm");
	
	web_reg_find("Text=Thank you for booking through Web Tours.",LAST);

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
		"Name=seatPref", "Value={RandomPref}", ENDITEM, 
		"Name=seatType", "Value={RandomType}", ENDITEM,
		"Name=buyFlights.x", "Value=46", ENDITEM,
		"Name=buyFlights.y", "Value=11", ENDITEM,
		LAST);

	lr_end_transaction("PaymentsForm",LR_AUTO);
	lr_start_transaction("logout");

	web_reg_find("Text=Welcome to the Web Tours site.",LAST);
	
	web_revert_auto_header("Origin");

	lr_think_time(9);

	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t7.inf", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);
	lr_end_transaction("UC_03_BuyTickets",LR_AUTO);

	return 0;
}