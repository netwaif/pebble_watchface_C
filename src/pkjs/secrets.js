var GOOGLE_CLIENT_ID = '212759238890-afop3sud4s8cu3q39d1ilb99gssfl9q3.apps.googleusercontent.com';
var GOOGLE_CLIENT_SECRET = '';
var CONFIG_URL = 'http://netwaif.org.ru/pebble/configuration.html#';
var redirect_uri = 'http://netwaif.org.ru/pebble/catchauth.html';

//https://www.googleapis.com/calendar/v3/calendars/primary/events?singleEvents=true&orderBy=startTime&timeMin=2017-03-28T00:00:00Z&maxResults=10
var test_events = {
    "nextPageToken": "EiUKGm50YnQxb211MGdja2diaDA0c2lta25nZ2lvGID0y4vu_tIC",
    "kind": "calendar#events",
    "defaultReminders": [],
    "items": [
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
                "dateTime": "2017-03-28T07:00:00+02:00"
            },
            "created": "2017-03-26T11:31:24.000Z",
            "iCalUID": "1b60kj3uofcec9jlga36l6vfos@google.com",
            "reminders": {
                "useDefault": true
            },
            "htmlLink": "https://www.google.com/calendar/event?eid=MWI2MGtqM3VvZmNlYzlqbGdhMzZsNnZmb3MgbmV0d2FpZkBt",
            "sequence": 3,
            "updated": "2017-03-26T11:46:47.503Z",
            "summary": "test1",
            "start": {
                "dateTime": "2017-03-28T04:00:00+02:00"
            },
            "etag": "\"2981057615006000\"",
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
        },
        {
            "status": "confirmed",
            "kind": "calendar#event",
            "end": {
                "dateTime": "2017-03-31T00:00:00+02:00"
            },
            "created": "2017-03-13T09:40:15.000Z",
            "iCalUID": "7m5g97ao2ok95daok6a483puk4@google.com",
            "reminders": {
                "useDefault": true
            },
            "htmlLink": "https://www.google.com/calendar/event?eid=N201Zzk3YW8yb2s5NWRhb2s2YTQ4M3B1azQgbmV0d2FpZkBt",
            "sequence": 0,
            "updated": "2017-03-13T18:40:38.143Z",
            "summary": "\u041f\u0435\u0440\u0435\u0435\u0437\u0434: \u0441\u0431\u043e\u0440 \u0432\u0435\u0449\u0435\u0439",
            "start": {
                "dateTime": "2017-03-30T13:00:00+02:00"
            },
            "etag": "\"2978860876286000\"",
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
            "id": "7m5g97ao2ok95daok6a483puk4"
        },
        {
            "status": "confirmed",
            "kind": "calendar#event",
            "end": {
                "dateTime": "2017-03-30T14:10:00+02:00"
            },
            "created": "2017-03-23T08:44:31.000Z",
            "iCalUID": "rrjpe1gecrc7kql8joc7hdc7mk@google.com",
            "reminders": {
                "overrides": [
                    {
                        "minutes": 60,
                        "method": "popup"
                    }
                ],
                "useDefault": false
            },
            "htmlLink": "https://www.google.com/calendar/event?eid=cnJqcGUxZ2VjcmM3a3FsOGpvYzdoZGM3bWsgbmV0d2FpZkBt",
            "sequence": 0,
            "updated": "2017-03-23T08:44:31.456Z",
            "summary": "\u041c\u0430\u043c\u0430 IST->FRA TK1591",
            "start": {
                "dateTime": "2017-03-30T14:10:00+02:00"
            },
            "etag": "\"2980517342810000\"",
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
            "id": "rrjpe1gecrc7kql8joc7hdc7mk"
        },
        {
            "status": "confirmed",
            "kind": "calendar#event",
            "end": {
                "dateTime": "2017-03-30T20:00:00+02:00"
            },
            "created": "2017-03-23T17:45:19.000Z",
            "iCalUID": "ntbt1omu0gckgbh04simknggio@google.com",
            "reminders": {
                "overrides": [
                    {
                        "minutes": 1440,
                        "method": "popup"
                    }
                ],
                "useDefault": false
            },
            "htmlLink": "https://www.google.com/calendar/event?eid=bnRidDFvbXUwZ2NrZ2JoMDRzaW1rbmdnaW8gbmV0d2FpZkBt",
            "sequence": 1,
            "updated": "2017-03-23T17:46:18.608Z",
            "summary": "FS Alumni: Bain&Company",
            "start": {
                "dateTime": "2017-03-30T18:30:00+02:00"
            },
            "etag": "\"2980582298364000\"",
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
            "id": "ntbt1omu0gckgbh04simknggio"
        }
    ],
    "updated": "2017-03-26T11:46:47.635Z",
    "summary": "netwaif",
    "etag": "\"p32s91re0hjqd40g\"",
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

