var MessageQueue = require("./lib/js-message-queue.js");
var secrets = require("./secrets");

function handle_appmessage_events(payload){
	return;
}

function handle_appmessage_busy(m){
	console.log("handling msg BUSY: "+m);
	if ('REQUEST' == m.operation){
		return;
	}else{
		return;
	}
}

function message_handler(event) {

	var msg = event.payload;
	console.log("msg received: " + msg);
	
	if ('BUSY' == msg.group) {
      handle_appmessage_busy(msg);
    }else if ('EVENTS' == msg.group){
			handle_appmessage_events(msg);
		}else if ('PING' == msg.group){
			return;
		}
}

Pebble.addEventListener('ready', function () {
    try {
      Pebble.addEventListener('appmessage', message_handler);
			MessageQueue.sendAppMessage({ group: 'BUSY', operation: 'UPDATE', data: '6|1|4|8|15|24|35|47|68|80|98|104|135' });
    }
    catch (ex) {
      console.log(ex);
    }
  });