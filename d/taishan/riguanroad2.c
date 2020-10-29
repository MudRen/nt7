// Room: /d/taishan/riguanroad2.c
// Last Modified by Lonely on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "日观小路");
        set("long", @LONG
这里是日观峰小路，自峰顶东下，联结东天门。此处山势陡峭，两
边下临深谷，一不小心都会掉了下去。
LONG );
        set("exits", ([
                "east"  : __DIR__"dongtian",
                "west"  : __DIR__"dongling",
        ]));
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 70);
	set("coor/y", 300);
	set("coor/z", 190);
	setup();
        replace_program(ROOM);
}