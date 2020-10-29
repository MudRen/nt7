//Room: /d/dali/heilongling.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","黑龙岭");
        set("long", @LONG
黑龙岭上有红梅二株，干已剥蚀贻尽，仅存枯皮，古质斑斓，横
卧于地，离奇乔异，如骄龙，如横峰，而花朵攒躜，又如锦片，如火
球，清芳袭人，不知植自何代，相传以为唐梅，疑或然也。南面就是
黑龙潭。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/xiaodao1",
            "south"      : "/d/dali/shulinwai",
            "southwest"  : "/d/dali/xiaodao2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19110);
	set("coor/y", -6900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}