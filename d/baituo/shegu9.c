// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蛇谷树林");
        set("long", @LONG
这是白驼山的蛇谷之中，林木葱郁，草丛中不时响起沙沙之声，
似乎有什麽在草里来回窜动。
LONG );

        set("exits", ([ 
            "east" : __DIR__"shegu8",
            "southwest" : __DIR__"shegu10",
        ]));

        set("objects", ([
            __DIR__"obj/branch"+(1+random(4)) : 1,
            __DIR__"npc/yetu" : 2,
        ]));

        set("hide_snake", random(3));
        set("grass", 1);

        set("cost", 2);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -50020);
        set("coor/y", 20170);
        set("coor/z", 20);
        setup();
}

#include "snake_room.h"