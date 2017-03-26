var GOOGLE_CLIENT_ID = '212759238890-afop3sud4s8cu3q39d1ilb99gssfl9q3.apps.googleusercontent.com';
var GOOGLE_CLIENT_SECRET = '';
var CONFIG_URL = 'http://netwaif.org.ru/pebble/configuration.html#';
var redirect_uri = 'http://netwaif.org.ru/pebble/catchauth.html';

//https://www.googleapis.com/calendar/v3/calendars/primary/events?singleEvents=true&orderBy=startTime&timeMin=2017-03-28T00:00:00Z&maxResults=10
var test_events = {
    "nextPageToken": "ElkKTl82OG8zMmRwZzY4cDNhbDFoNjBwajRjMW9iOG1taWdyMWRncTZrZzM2ZWNtbTRyMWQ2MHAyc29qMWRwbG0ycXIxY2hpbXFxYjU1cGk2YRiAyOHX7v3SAg==",
    "kind": "calendar#events",
    "defaultReminders": [],
    "items": [
        {
            "status": "confirmed",
            "kind": "calendar#event",
            "end": {
                "dateTime": "2017-03-27T00:00:00+02:00"
            },
            "created": "2017-03-26T11:31:24.000Z",
            "iCalUID": "1b60kj3uofcec9jlga36l6vfos@google.com",
            "reminders": {
                "useDefault": true
            },
            "htmlLink": "https://www.google.com/calendar/event?eid=MWI2MGtqM3VvZmNlYzlqbGdhMzZsNnZmb3MgbmV0d2FpZkBt",
            "sequence": 7,
            "updated": "2017-03-26T14:39:15.656Z",
            "summary": "test1",
            "start": {
                "dateTime": "2017-03-26T23:00:00+02:00"
            },
            "etag": "\"2981078311312000\"",
            "organizer": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "creator": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "id": "1b60kj3uofcec9jlga36l6vfos"
        },
        {
            "status": "confirmed",
            "kind": "calendar#event",
            "end": {
                "date": "2017-03-31"
            },
            "attachments": [
                {
                    "fileUrl": "https://drive.google.com/file/d/0B252JBocQfzyX2NJRl9KWTkwQTQ/view?usp=drive_web",
                    "iconLink": "https://ssl.gstatic.com/docs/doclist/images/icon_10_generic_list.png",
                    "fileId": "0B252JBocQfzyX2NJRl9KWTkwQTQ",
                    "title": "Moving Out FS Dorms - 22.04.2016.pdf"
                },
                {
                    "fileUrl": "https://drive.google.com/file/d/0B252JBocQfzya0JQWkpDa0lBWUk/view?usp=drive_web",
                    "iconLink": "https://ssl.gstatic.com/docs/doclist/images/icon_10_generic_list.png",
                    "fileId": "0B252JBocQfzya0JQWkpDa0lBWUk",
                    "title": "Moving out procedure - 30 06 2016.pdf"
                },
                {
                    "fileUrl": "https://drive.google.com/file/d/0B252JBocQfzyaEFLWTJFVjZ4Qkk/view?usp=drive_web",
                    "iconLink": "https://ssl.gstatic.com/docs/doclist/images/icon_10_generic_list.png",
                    "fileId": "0B252JBocQfzyaEFLWTJFVjZ4Qkk",
                    "title": "room_checklist.pdf"
                }
            ],
            "created": "2017-03-13T15:30:00.000Z",
            "iCalUID": "27pqocg9pn0t691abeb0mv2rjs@google.com",
            "reminders": {
                "useDefault": false
            },
            "htmlLink": "https://www.google.com/calendar/event?eid=MjdwcW9jZzlwbjB0NjkxYWJlYjBtdjJyanMgbmV0d2FpZkBt",
            "sequence": 0,
            "updated": "2017-03-19T23:11:51.323Z",
            "summary": "\u041f\u0435\u0440\u0435\u0435\u0437\u0434: \u043f\u043e\u0434\u0433\u043e\u0442\u043e\u0432\u043a\u0430",
            "start": {
                "date": "2017-03-27"
            },
            "etag": "\"2979384112307000\"",
            "transparency": "transparent",
            "attendees": [
                {
                    "responseStatus": "accepted",
                    "organizer": true,
                    "displayName": "Roman Frolov",
                    "email": "netwaif@gmail.com",
                    "self": true
                }
            ],
            "organizer": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "creator": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "id": "27pqocg9pn0t691abeb0mv2rjs"
        },
        {
            "status": "confirmed",
            "kind": "calendar#event",
            "end": {
                "date": "2017-03-28"
            },
            "created": "2017-03-13T09:36:29.000Z",
            "iCalUID": "g6si0h1pajj80dd6gqtovskgc8@google.com",
            "reminders": {
                "overrides": [
                    {
                        "minutes": 840,
                        "method": "popup"
                    }
                ],
                "useDefault": false
            },
            "htmlLink": "https://www.google.com/calendar/event?eid=ZzZzaTBoMXBhamo4MGRkNmdxdG92c2tnYzggbmV0d2FpZkBt",
            "sequence": 0,
            "updated": "2017-03-13T09:36:29.458Z",
            "summary": "Immo: \u043f\u0435\u0440\u0435\u0432\u043e\u0434 miete+kaution",
            "start": {
                "date": "2017-03-27"
            },
            "etag": "\"2978795578825000\"",
            "transparency": "transparent",
            "organizer": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "creator": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "id": "g6si0h1pajj80dd6gqtovskgc8"
        },
        {
            "status": "confirmed",
            "kind": "calendar#event",
            "end": {
                "timeZone": "Europe/Berlin",
                "dateTime": "2017-03-27T09:30:00+02:00"
            },
            "created": "2017-03-06T12:01:51.000Z",
            "iCalUID": "6hj68p1o6grm6bb56gpjeb9kcgqj0b9ockp3ab9j6opj4dpk6com6p9pc4@google.com",
            "reminders": {
                "overrides": [
                    {
                        "minutes": 720,
                        "method": "popup"
                    },
                    {
                        "minutes": 60,
                        "method": "popup"
                    }
                ],
                "useDefault": false
            },
            "htmlLink": "https://www.google.com/calendar/event?eid=NmhqNjhwMW82Z3JtNmJiNTZncGplYjlrY2dxajBiOW9ja3AzYWI5ajZvcGo0ZHBrNmNvbTZwOXBjNCBuZXR3YWlmQG0",
            "sequence": 0,
            "updated": "2017-03-06T12:01:51.224Z",
            "summary": "Ortho: Dr. Loth",
            "start": {
                "timeZone": "Europe/Berlin",
                "dateTime": "2017-03-27T09:00:00+02:00"
            },
            "etag": "\"2977603422343000\"",
            "organizer": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "creator": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "id": "6hj68p1o6grm6bb56gpjeb9kcgqj0b9ockp3ab9j6opj4dpk6com6p9pc4"
        },
        {
            "status": "confirmed",
            "kind": "calendar#event",
            "end": {
                "dateTime": "2017-03-27T10:25:00+02:00"
            },
            "created": "2017-03-06T18:40:19.000Z",
            "iCalUID": "5dlqd5ilmhivaccqcp98mnn7ts@google.com",
            "reminders": {
                "overrides": [
                    {
                        "minutes": 720,
                        "method": "popup"
                    },
                    {
                        "minutes": 60,
                        "method": "popup"
                    }
                ],
                "useDefault": false
            },
            "htmlLink": "https://www.google.com/calendar/event?eid=NWRscWQ1aWxtaGl2YWNjcWNwOThtbm43dHMgbmV0d2FpZkBt",
            "sequence": 0,
            "updated": "2017-03-06T18:40:51.844Z",
            "summary": "\u0410\u043d\u044f: \u043f\u0440\u0438\u043b\u0435\u0442",
            "start": {
                "dateTime": "2017-03-27T10:25:00+02:00"
            },
            "etag": "\"2977651303601000\"",
            "organizer": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "creator": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "id": "5dlqd5ilmhivaccqcp98mnn7ts"
        },
        {
            "status": "confirmed",
            "kind": "calendar#event",
            "end": {
                "dateTime": "2017-03-28T20:00:00+02:00"
            },
            "created": "2017-03-21T11:01:45.000Z",
            "iCalUID": "o0am5ltrlaefv7al22mhieep20@google.com",
            "reminders": {
                "overrides": [
                    {
                        "minutes": 60,
                        "method": "popup"
                    },
                    {
                        "minutes": 1440,
                        "method": "popup"
                    }
                ],
                "useDefault": false
            },
            "htmlLink": "https://www.google.com/calendar/event?eid=bzBhbTVsdHJsYWVmdjdhbDIybWhpZWVwMjAgbmV0d2FpZkBt",
            "sequence": 0,
            "updated": "2017-03-21T11:01:45.467Z",
            "summary": "DHL Presentation",
            "start": {
                "dateTime": "2017-03-28T18:00:00+02:00"
            },
            "etag": "\"2980188210825000\"",
            "location": "FS Room 20",
            "organizer": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "creator": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "id": "o0am5ltrlaefv7al22mhieep20"
        },
        {
            "status": "confirmed",
            "kind": "calendar#event",
            "end": {
                "dateTime": "2017-03-29T12:15:00+02:00"
            },
            "description": "Studienort: Frankfurt School of Finance & Management gGmbH\nSonnemannstra\u00dfe 9-11, 60314 Frankfurt am Main\n",
            "created": "2017-02-17T09:58:02.000Z",
            "iCalUID": "20170225T103207Z-iCal4j@fs-bl-02.bankakademie.de",
            "reminders": {
                "useDefault": true
            },
            "htmlLink": "https://www.google.com/calendar/event?eid=XzY4bzMyZHBnNjhwM2FsMWg2MHBqNGMxbmI4bW1pZ3IxZGdxNmtnMzZlY21tNHIxZDYwcDJzb2oxZHBsbTJxcjFjaGltcXFiNTVwaTZhIG5ldHdhaWZAbQ",
            "sequence": 2174,
            "updated": "2017-02-17T09:58:49.975Z",
            "summary": "C 1  # 9 German - Level C 1 Frankfurt am Main   Gabriela Lund\n",
            "start": {
                "dateTime": "2017-03-29T09:00:00+02:00"
            },
            "etag": "\"2974651059950000\"",
            "location": "NB12 (Frankfurt School of Finance & Management gGmbH)",
            "organizer": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "creator": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "id": "_68o32dpg68p3al1h60pj4c1nb8mmigr1dgq6kg36ecmm4r1d60p2soj1dplm2qr1chimqqb55pi6a"
        },
        {
            "status": "confirmed",
            "kind": "calendar#event",
            "end": {
                "dateTime": "2017-03-29T22:00:00+02:00"
            },
            "created": "2017-02-16T11:08:02.000Z",
            "iCalUID": "sqb9chf2aepe1uispl8vjqkquc@google.com",
            "reminders": {
                "overrides": [
                    {
                        "minutes": 120,
                        "method": "popup"
                    },
                    {
                        "minutes": 60,
                        "method": "popup"
                    },
                    {
                        "minutes": 1440,
                        "method": "popup"
                    }
                ],
                "useDefault": false
            },
            "htmlLink": "https://www.google.com/calendar/event?eid=c3FiOWNoZjJhZXBlMXVpc3BsOHZqcWtxdWMgbmV0d2FpZkBt",
            "sequence": 0,
            "updated": "2017-02-16T11:08:03.018Z",
            "summary": "?Deloitte: Kochabend?",
            "start": {
                "dateTime": "2017-03-29T18:00:00+02:00"
            },
            "etag": "\"2974486565931000\"",
            "location": "Die Genussakademie Westend, R\u00fcsterstra\u00dfe 1, 60313 Frankfurt am Main, Germany",
            "organizer": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "creator": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "id": "sqb9chf2aepe1uispl8vjqkquc"
        },
        {
            "status": "confirmed",
            "kind": "calendar#event",
            "end": {
                "dateTime": "2017-03-30T09:00:00+02:00"
            },
            "created": "2017-01-27T13:39:01.000Z",
            "iCalUID": "vkrq7r6r12vcn5f66hpj5fa6pc@google.com",
            "reminders": {
                "overrides": [
                    {
                        "minutes": 720,
                        "method": "popup"
                    },
                    {
                        "minutes": 60,
                        "method": "popup"
                    }
                ],
                "useDefault": false
            },
            "htmlLink": "https://www.google.com/calendar/event?eid=dmtycTdyNnIxMnZjbjVmNjZocGo1ZmE2cGMgbmV0d2FpZkBt",
            "sequence": 0,
            "updated": "2017-01-27T13:39:01.547Z",
            "summary": "FS: Group Speakers breakfast",
            "start": {
                "dateTime": "2017-03-30T08:00:00+02:00"
            },
            "etag": "\"2971048683003000\"",
            "location": "FS Room 5",
            "organizer": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "creator": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "id": "vkrq7r6r12vcn5f66hpj5fa6pc"
        },
        {
            "status": "confirmed",
            "kind": "calendar#event",
            "end": {
                "dateTime": "2017-03-30T12:15:00+02:00"
            },
            "description": "Studienort: Frankfurt School of Finance & Management gGmbH\nSonnemannstra\u00dfe 9-11, 60314 Frankfurt am Main\n",
            "created": "2017-02-17T09:58:02.000Z",
            "iCalUID": "20170225T103208Z-iCal4j@fs-bl-02.bankakademie.de",
            "reminders": {
                "useDefault": true
            },
            "htmlLink": "https://www.google.com/calendar/event?eid=XzY4bzMyZHBnNjhwM2FsMWg2MHBqNGMxb2I4bW1pZ3IxZGdxNmtnMzZlY21tNHIxZDYwcDJzb2oxZHBsbTJxcjFjaGltcXFiNTVwaTZhIG5ldHdhaWZAbQ",
            "sequence": 2174,
            "updated": "2017-02-17T09:58:49.975Z",
            "summary": "FIN71050  Financial Markets and Institutions Frankfurt am Main   Prof. Dr. Falko Fecht\n",
            "start": {
                "dateTime": "2017-03-30T09:00:00+02:00"
            },
            "etag": "\"2974651059950000\"",
            "location": "05 (Frankfurt School of Finance & Management gGmbH)",
            "organizer": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "creator": {
                "self": true,
                "displayName": "Roman Frolov",
                "email": "netwaif@gmail.com"
            },
            "id": "_68o32dpg68p3al1h60pj4c1ob8mmigr1dgq6kg36ecmm4r1d60p2soj1dplm2qr1chimqqb55pi6a"
        }
    ],
    "updated": "2017-03-26T14:39:15.773Z",
    "summary": "netwaif",
    "etag": "\"p334ap7c7mfqd40g\"",
    "timeZone": "Europe/Berlin",
    "accessRole": "owner"
};

//https://www.googleapis.com/calendar/v3/freeBusy
// POST: {
//    "items": [
//    {
//        "id": "primary"
//    }
// ],
//    "timeMin": "2017-01-01T18:25:43.000Z",
//    "timeMax": "2017-02-28T18:25:43.000Z"
// }
var test_busy = {
 "kind": "calendar#freeBusy",
 "timeMin": "2017-01-01T18:25:43.000Z",
 "timeMax": "2017-02-28T18:25:43.000Z",
 "calendars": {
  "primary": {
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
module.exports.test_events = test_events;

