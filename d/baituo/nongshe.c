inherit ROOM;

void create()
{
        set("short", "农舍");
        set("long", @LONG
这里是一间小农舍，家具很新。看来主人比较富裕。
LONG );
        set("exits", ([
                "west" : __DIR__"guangchang",
        ]));
        set("objects",([
                __DIR__"npc/woman" : 1,
        ]));
        set("coor/x", -49980);
        set("coor/y", 19980);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}