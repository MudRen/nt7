// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("贾宝玉[2;37;0m[2;37;0m", ({"jbaoyu"}));        
        set("gender", "男性");                
        set("long", "贾宝玉[2;37;0m
它是晴雯的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hqingwen");
        set("owner_name", "晴雯");
        set_temp("owner", "hqingwen");
        set_temp("owner_name", "晴雯");
        ::setup();
}
