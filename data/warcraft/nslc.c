// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "女性");                
        set("long", "23456[2;37;0m
它是吹大地的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "nslc");
        set("owner_name", "吹大地");
        set_temp("owner", "nslc");
        set_temp("owner_name", "吹大地");
        ::setup();
}
