# mir3_client_3.55

It's from here:
https://www.lomcn.org/forum/threads/functional-official-3g-client-source-code.108457/

Hi guys. That's a long time since I last posted something here. Some time ago someone linked leaked source code for the client here and I decided to check it out. After a few hours of hacking I got it to compile with MSVC 2019 and work with 3.55 files, which was a little surprising TBH. The client does not need the Holley launcher too. The source code is buggy though, and it would require some effort to make it run smoothly. I'm wondering if there's anyone who would appreciate me spending some time on that project. Especially so given we already have something to work with with the Zircon files. I would not think twice about investing some time into it if there was source code for the server too, but unfortunately there isn't. Not even the eiserver.exe with an injected DLL type of thing like holley or king. So it seems kind of pointless. What do you guys think?

These clients don't really have assassin, but they mention it:
Code:
#define _JOB_GUNGSA                    3
#define _JOB_DOSA                    2
#define _JOB_SULSA                    1
#define _JOB_JUNSA                    0
or
Code:
#define _CHR_CHR_CREATE_ARCHER            5
There isn't anything besides character creation.

leaked in 2008?
Looks like the files were last modified in November of 2006

kr us cn ?
All of the above. I see differences between the clients, but there aren't too many IMO.

I took the files from this thread where @ryancg uploaded it. I reuploaded it here - download, I think they belong to mirfiles.
In mirfiles there is also source code for an old version of the server and the client there also looks fine, it uses JOB interface.

The Zircon files are great, I spent a few days playing on the SEA Eden server and they were amazing, but there are subtle differences to what I remember from my youth. To recreate the server behaviour of 3.55 and older files without the source code I think it would be a tremendous amount of work. I know serveral people here are capable of doing that, I'm also a successful software engineer now, but it's too much to me.
Anyway, if someone needed help with C++ or software engineering in general related to mir3 - PM me.


Its not too much effort to use the mir2 server as a base, since you know how the client is handling the packets. The amount of work involved porting the client to a more modern graphics system and implementing the mir3 logic in server, could take months.

