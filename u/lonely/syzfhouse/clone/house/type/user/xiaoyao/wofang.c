// wofang.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "卧房");
    set("long", @LONG
一间小小的卧房。
LONG);

    set("exits",
    ([
        "north" : __DIR__"houyuan",
        "south" : __DIR__"xiaoting",
    ]));

    set("sleep_room", 1);
    set("no_fight", 1);
    set("no_learn", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");

    setup();
    restore();
}
