// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"xing"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是冰晓的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "axing");
        set("owner_name", "冰晓");
        set_temp("owner", "axing");
        set_temp("owner_name", "冰晓");
        ::setup();
}
