var GOOGLE_CLIENT_ID = '212759238890-afop3sud4s8cu3q39d1ilb99gssfl9q3.apps.googleusercontent.com';
var GOOGLE_CLIENT_SECRET = '';
var CONFIG_URL = 'http://netwaif.org.ru/pebble/configuration.html#';
var redirect_uri = 'http://netwaif.org.ru/pebble/catchauth.html';
var test_busy = {
 "kind": "calendar#freeBusy",
 "timeMin": "2017-01-01T18:25:43.000Z",
 "timeMax": "2017-02-28T18:25:43.000Z",
 "calendars": {
  "netwaif@gmail.com": {
   "busy": [
    {
     "start": "2017-01-09T00:12:00Z",
     "end": "2017-01-09T00:55:00Z"
    },
    {
     "start": "2017-01-11T02:00:00Z",
     "end": "2017-01-11T03:30:00Z"
    },
    {
     "start": "2017-01-22T06:54:00Z",
     "end": "2017-01-22T08:12:00Z"
    },
    {
     "start": "2017-01-22T11:35:00Z",
     "end": "2017-01-23T13:24:00Z"
    },
    {
     "start": "2017-01-23T14:00:00Z",
     "end": "2017-01-23T15:30:00Z"
    },
    {
     "start": "2017-01-26T20:30:00Z",
     "end": "2017-01-26T23:36:00Z"
    }
   ]
  }
 }
};

module.exports.GOOGLE_CLIENT_ID = GOOGLE_CLIENT_ID;
module.exports.GOOGLE_CLIENT_SECRET = GOOGLE_CLIENT_SECRET;
module.exports.CONFIG_URL = CONFIG_URL;
module.exports.redirect_uri = redirect_uri;
module.exports.test_busy = test_busy;

