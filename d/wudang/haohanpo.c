inherit ROOM;

void create()
{
        set("short","好汉坡");
        set("long", @LONG
此处连绵十几里山势陡峭，名为好汉坡，山路两旁种满了细竹，
翠色横空景象怡人，不知不觉让你忘记爬坡的疲劳。坡顶有一座回龙
观，是展望岳顶的最佳去处，但见天柱峰青紫插天，如在眼前，而相
去实际上还有五十里。
LONG );
        set("exits", ([
                "northdown": __DIR__"wdbl",
                "southdown": __DIR__"shanlu1",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -370);
        set("coor/y", -220);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}