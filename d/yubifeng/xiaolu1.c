// /yubifeng/xiaolu1.c
// Last modified by Lonely 2003.9.2

inherit ROOM;

void create()
{
        set("short", "大松林");
        set("long", @LONG
这是一片茂密的松林，杂乱的生长在倾斜的山坡上。林中松树都是
数百年的老树，枝柯交横，树顶上压了数尺厚的白雪，是以林中雪少，
反而好走。
LONG );
        set("exits", ([
                "west"  : __DIR__"songlin4",
                "east"  : __FILE__,
                "south" : __DIR__"xiaolu2",
                "north" : __FILE__,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yubifeng");
        set("coor/x", 6110);
        set("coor/y", 5150);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}