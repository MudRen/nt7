// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是金藕的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "godoo");
        set("owner_name", "金藕");
        set_temp("owner", "godoo");
        set_temp("owner_name", "金藕");
        ::setup();
}
