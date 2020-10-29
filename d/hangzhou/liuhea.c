// liuhea.c
// Date: Nov.1997 by Java
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "六和塔");
        set("long", @LONG
这里是六和塔的十层。窗(window)外是浓妆淡抹的西子湖，塔
中玲珑八角，青砖砌地，雕栏飞檐间粘连了些许蛛网。
LONG);
        set("exits", ([
            "down"  : __DIR__"liuhe9",
            "up"    : __DIR__"liuheb",
        ]));
        set("objects", ([
            __DIR__"honghua/zhou" :1,
        ]));
        set("item_desc", ([
            "window": "从窗口望出去，钱江东去。近处农田中，有一农夫正荷锄耕耘。\n",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 759);
	set("coor/y", -2121);
	set("coor/z", 99);
	setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "up" &&
            objectp(present("zhou zhongying", environment(me))))
            return notify_fail("周仲英吹着白胡子，挡在楼梯口。\n");
        return ::valid_leave(me, dir);
}