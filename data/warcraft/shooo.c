// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是彼得翻的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shooo");
        set("owner_name", "彼得翻");
        set_temp("owner", "shooo");
        set_temp("owner_name", "彼得翻");
        ::setup();
}
