inherit ROOM;

void create()
{
  set("short","松树林");
  set("long",@LONG
这里是一片茂密的松树林，松树高大，枝叶茂盛，你一走进来差
点便迷失了方向。一条长廊由西向东通往松林深处。
LONG);

     set("outdoors", "天龙寺");
     set("exits",([
           "east" : __FILE__,
           "west" : __DIR__"songlin-3",
           "north" : __DIR__"songlin1",
           "south" : __DIR__"songlin1",
     ]));
    
     set("coor/x",-300);
  set("coor/y",-290);
   set("coor/z",40);
   setup();
}
