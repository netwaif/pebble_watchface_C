var MessageQueue = require("./lib/js-message-queue.js");
var secrets = require("./secrets.js");

function handle_appmessage_events(payload){
	return;
}

function handle_appmessage_busy(m){
	console.log("handling msg BUSY: "+JSON.stringify(m));
	if ('REQUEST' == m.operation){
		var response;
		response = '6|1|4|8|15|24|35|47|68|80|98|104|135';
		response = busy_stringify(secrets.test_busy.calendars['netwaif@gmail.com'].busy);
		MessageQueue.sendAppMessage({ group: 'BUSY', operation: 'UPDATE', data: response});
		return;
	}else{
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
	console.log(res);
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


