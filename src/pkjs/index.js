var MessageQueue = require("./lib/js-message-queue.js");
var secrets = require("./secrets.js");


function handle_appmessage_busy(m){
	console.log("handling msg BUSY: "+JSON.stringify(m));
	if ('REQUEST' == m.operation){
		var response;
		//response = '6|1|4|8|15|24|35|47|68|80|98|104|135';
		response = busy_stringify(secrets.test_busy.calendars['primary'].busy);
		MessageQueue.sendAppMessage({ group: 'BUSY', operation: 'UPDATE', data: response});
		return;
	}else{
		return;
	}
}

function handle_appmessage_events(m){
	console.log("handling msg EVENTS: "+ JSON.stringify(m));
	if ('REQUEST' == m.operation){
		var response;
		//response = "14:30 test event 1\n+1 12:00 тестовое сообщение";
		response = events_stringify(secrets.test_events.items);

		MessageQueue.sendAppMessage({group: 'EVENTS', operation: 'UPDATE', data: response});
		return;
	} else {
		return;
	}
}

function message_handler(event) {

	var msg = event.payload;
	console.log("msg received: " + JSON.stringify(msg));
	
	if ('BUSY' == msg.group) {
		handle_appmessage_busy(msg);
    }else if ('EVENTS' == msg.group){
		handle_appmessage_events(msg);
	}else if ('PING' == msg.group){
		return;
	}
}

function events_stringify(events){
    var count = 0;
    var res ='';
    for (var i=0;i<events.length;++i){
    	if (events[i].start.dateTime != null && events[i].end.dateTime != null){
        	var start = new Date(events[i].start.dateTime);
        	start.setHours(start.getHours() + start.getTimezoneOffset() / 60);
        	res = res + '|' + start.getTime();
        	var end = new Date(events[i].end.dateTime);
        	end.setHours(end.getHours() + end.getTimezoneOffset() / 60);
        	res = res + '|' + end.getTime();
        	var sum = events[i].summary.toString();
            var now = new Date(Date.now());
        	var next_day = (start.getYear()-now.getYear())*365+(start.getMonth()-now.getMonth())*30+(start.getDate()-now.getDate());
            start.setHours(start.getHours() - start.getTimezoneOffset() / 60);
            end.setHours(end.getHours() - end.getTimezoneOffset() / 60);
        	res = res + ((next_day>0)?'|+':'|')
				+ ((start.getHours()<10)?'0':'') + start.getHours() + ':'
				+ ((start.getMinutes()<10)?'0':'') + start.getMinutes() + ' '
				+ sum.slice(0,32);
        	count++;
	   	}else if(events[i].start.date!=null && events[i].end.date!=null){
			//count++;
		}
    }
    res = count + ((count==0)?'|':'') + res;
    console.log("EVENTS stringify (out of "+events.length +"): " + res);
    return res;
}

function busy_stringify(busy){
	var res = busy.length;
	var i;
	for (i=0;i<busy.length;++i){
		var start = new Date(busy[i].start);
		start.setHours(start.getHours() + start.getTimezoneOffset() / 60);
		var end = new Date(busy[i].end);
		end.setHours(end.getHours() + end.getTimezoneOffset() / 60);
		res = res + '|'+ Math.floor((start.getHours()*60+start.getMinutes())/12) + '|'+ (Math.round((end.getHours()*60+end.getMinutes())/12));
	}
	console.log("BUSY stringify: "+res);
	return res;
}

Pebble.on('ready', function () {
    try {
			Pebble.addEventListener('appmessage', message_handler);
			MessageQueue.sendAppMessage({ group: 'SYS', operation: 'INIT', data: 'OK' });
		}
    catch (ex) {
      console.log(ex);
    }
  });


