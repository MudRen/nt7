// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinlong"}));        
        set("gender", "男性");                
        set("long", "  [2;37;0m
它是钱打二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "daqianb");
        set("owner_name", "钱打二");
        set_temp("owner", "daqianb");
        set_temp("owner_name", "钱打二");
        ::setup();
}
