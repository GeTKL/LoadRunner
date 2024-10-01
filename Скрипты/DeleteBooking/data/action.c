Action()
{

	lr_start_transaction("UC_05_DeleteBooking");

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

	web_websocket_send("ID=1", 
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1727734884245\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);

	/*Connection ID 1 received buffer WebSocketReceive0*/

	lr_end_transaction("open_WebTours",LR_AUTO);

	lr_start_transaction("login");

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

	web_image("Itinerary Button", 
		"Alt=Itinerary Button", 
		"Snapshot=t3.inf", 
		LAST);

	lr_end_transaction("open_bookingPages",LR_AUTO);

	lr_start_transaction("deleteBooking");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(18);

	web_submit_data("itinerary.pl", 
		"Action=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=1", "Value=on", ENDITEM, 
		"Name=flightID", "Value=210297424-100296-JB", ENDITEM, 
		"Name=flightID", "Value=210297416-177189-JB", ENDITEM, 
		"Name=flightID", "Value=210297416-254112-JB", ENDITEM, 
		"Name=flightID", "Value=210297424-331066-JB", ENDITEM, 
		"Name=flightID", "Value=210297424-407989-JB", ENDITEM, 
		"Name=flightID", "Value=33492785-48-JB", ENDITEM, 
		"Name=flightID", "Value=0-0-P", ENDITEM, 
		"Name=flightID", "Value=0-0-M", ENDITEM, 
		"Name=flightID", "Value=4-0-60", ENDITEM, 
		"Name=flightID", "Value=8-0-60", ENDITEM, 
		"Name=flightID", "Value=1-0-60", ENDITEM, 
		"Name=flightID", "Value=0-0-5\r\n", ENDITEM, 
		"Name=flightID", "Value=6-1-5\r\n", ENDITEM, 
		"Name=flightID", "Value=8-1-5\r\n", ENDITEM, 
		"Name=flightID", "Value=12-1-5\r\n", ENDITEM, 
		"Name=flightID", "Value=15-1-5\r\n", ENDITEM, 
		"Name=flightID", "Value=21-1-5\r\n", ENDITEM, 
		"Name=flightID", "Value=23-1-10", ENDITEM, 
		"Name=flightID", "Value=23-1-\r\n", ENDITEM, 
		"Name=flightID", "Value=23-1-10", ENDITEM, 
		"Name=flightID", "Value=23-1-10", ENDITEM, 
		"Name=flightID", "Value=23-1-10", ENDITEM, 
		"Name=flightID", "Value=23-1-10", ENDITEM, 
		"Name=flightID", "Value=23-1-10", ENDITEM, 
		"Name=flightID", "Value=23-1-10", ENDITEM, 
		"Name=flightID", "Value=23-2-10", ENDITEM, 
		"Name=flightID", "Value=23-2-10", ENDITEM, 
		"Name=flightID", "Value=23-2-10", ENDITEM, 
		"Name=flightID", "Value=23-2-\r\n", ENDITEM, 
		"Name=flightID", "Value=23-2-10", ENDITEM, 
		"Name=flightID", "Value=23-2-10", ENDITEM, 
		"Name=flightID", "Value=23-2-10", ENDITEM, 
		"Name=flightID", "Value=23-2-10", ENDITEM, 
		"Name=flightID", "Value=23-2-10", ENDITEM, 
		"Name=flightID", "Value=23-2-10", ENDITEM, 
		"Name=flightID", "Value=23-2-10", ENDITEM, 
		"Name=flightID", "Value=23-2-10", ENDITEM, 
		"Name=flightID", "Value=23-2-10", ENDITEM, 
		"Name=flightID", "Value=23-3-10", ENDITEM, 
		"Name=flightID", "Value=23-3-10", ENDITEM, 
		"Name=flightID", "Value=23-3-10", ENDITEM, 
		"Name=flightID", "Value=36-3-10", ENDITEM, 
		"Name=flightID", "Value=4-3-10", ENDITEM, 
		"Name=flightID", "Value=4-3-10", ENDITEM, 
		"Name=flightID", "Value=27-3-10", ENDITEM, 
		"Name=flightID", "Value=17-3-10", ENDITEM, 
		"Name=flightID", "Value=4-3-10", ENDITEM, 
		"Name=flightID", "Value=33-3-10", ENDITEM, 
		"Name=flightID", "Value=17-3-10", ENDITEM, 
		"Name=flightID", "Value=15-3-10", ENDITEM, 
		"Name=flightID", "Value=34-3-10", ENDITEM, 
		"Name=flightID", "Value=11-4-10", ENDITEM, 
		"Name=flightID", "Value=8-4-10", ENDITEM, 
		"Name=flightID", "Value=36-4-00", ENDITEM, 
		"Name=flightID", "Value=0-4-\r\n", ENDITEM, 
		"Name=flightID", "Value=0-4-\r\n", ENDITEM, 
		"Name=flightID", "Value=3-4-\r\n", ENDITEM, 
		"Name=flightID", "Value=1-4-\r\n", ENDITEM, 
		"Name=flightID", "Value=0-45-\r\n", ENDITEM, 
		"Name=removeFlights.x", "Value=59", ENDITEM, 
		"Name=removeFlights.y", "Value=3", ENDITEM, 
		"Name=.cgifields", "Value=33", ENDITEM, 
		"Name=.cgifields", "Value=32", ENDITEM, 
		"Name=.cgifields", "Value=21", ENDITEM, 
		"Name=.cgifields", "Value=7", ENDITEM, 
		"Name=.cgifields", "Value=26", ENDITEM, 
		"Name=.cgifields", "Value=17", ENDITEM, 
		"Name=.cgifields", "Value=2", ENDITEM, 
		"Name=.cgifields", "Value=1", ENDITEM, 
		"Name=.cgifields", "Value=18", ENDITEM, 
		"Name=.cgifields", "Value=30", ENDITEM, 
		"Name=.cgifields", "Value=16", ENDITEM, 
		"Name=.cgifields", "Value=44", ENDITEM, 
		"Name=.cgifields", "Value=55", ENDITEM, 
		"Name=.cgifields", "Value=27", ENDITEM, 
		"Name=.cgifields", "Value=25", ENDITEM, 
		"Name=.cgifields", "Value=28", ENDITEM, 
		"Name=.cgifields", "Value=57", ENDITEM, 
		"Name=.cgifields", "Value=40", ENDITEM, 
		"Name=.cgifields", "Value=20", ENDITEM, 
		"Name=.cgifields", "Value=14", ENDITEM, 
		"Name=.cgifields", "Value=59", ENDITEM, 
		"Name=.cgifields", "Value=49", ENDITEM, 
		"Name=.cgifields", "Value=24", ENDITEM, 
		"Name=.cgifields", "Value=10", ENDITEM, 
		"Name=.cgifields", "Value=31", ENDITEM, 
		"Name=.cgifields", "Value=35", ENDITEM, 
		"Name=.cgifields", "Value=11", ENDITEM, 
		"Name=.cgifields", "Value=53", ENDITEM, 
		"Name=.cgifields", "Value=48", ENDITEM, 
		"Name=.cgifields", "Value=42", ENDITEM, 
		"Name=.cgifields", "Value=22", ENDITEM, 
		"Name=.cgifields", "Value=46", ENDITEM, 
		"Name=.cgifields", "Value=13", ENDITEM, 
		"Name=.cgifields", "Value=23", ENDITEM, 
		"Name=.cgifields", "Value=29", ENDITEM, 
		"Name=.cgifields", "Value=6", ENDITEM, 
		"Name=.cgifields", "Value=50", ENDITEM, 
		"Name=.cgifields", "Value=39", ENDITEM, 
		"Name=.cgifields", "Value=36", ENDITEM, 
		"Name=.cgifields", "Value=3", ENDITEM, 
		"Name=.cgifields", "Value=51", ENDITEM, 
		"Name=.cgifields", "Value=9", ENDITEM, 
		"Name=.cgifields", "Value=58", ENDITEM, 
		"Name=.cgifields", "Value=41", ENDITEM, 
		"Name=.cgifields", "Value=12", ENDITEM, 
		"Name=.cgifields", "Value=47", ENDITEM, 
		"Name=.cgifields", "Value=15", ENDITEM, 
		"Name=.cgifields", "Value=52", ENDITEM, 
		"Name=.cgifields", "Value=38", ENDITEM, 
		"Name=.cgifields", "Value=8", ENDITEM, 
		"Name=.cgifields", "Value=4", ENDITEM, 
		"Name=.cgifields", "Value=34", ENDITEM, 
		"Name=.cgifields", "Value=56", ENDITEM, 
		"Name=.cgifields", "Value=45", ENDITEM, 
		"Name=.cgifields", "Value=37", ENDITEM, 
		"Name=.cgifields", "Value=43", ENDITEM, 
		"Name=.cgifields", "Value=19", ENDITEM, 
		"Name=.cgifields", "Value=54", ENDITEM, 
		"Name=.cgifields", "Value=5", ENDITEM, 
		LAST);

	lr_end_transaction("deleteBooking",LR_AUTO);

	lr_think_time(10);

	lr_start_transaction("logout");

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