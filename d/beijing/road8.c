inherit ROOM;

void create()
{
        set("short", "大驿道");
        set("long", @LONG
你走在一条尘土飞扬的大驿道上。北上就是北京城。挑担子的、
行商的、赶着大车的马夫、上京赶考的书生，熙熙攘攘，非常热闹。
不时还有两三骑快马从身边飞驰而过，扬起一路尘埃。西边有个小摊，
许多人在那里歇息。
LONG );
        set("exits", ([
                "north" : "/d/beijing/road4",
                "south" : "/d/beijing/road9",
                "west" : "/d/beijing/xiaotan"                
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2770);
	set("coor/y", 7570);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}