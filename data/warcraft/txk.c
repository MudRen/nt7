// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大鸟[2;37;0m[2;37;0m", ({"quer"}));        
        set("gender", "女性");                
        set("long", "大[2;37;0m
它是邰玄的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "txk");
        set("owner_name", "邰玄");
        set_temp("owner", "txk");
        set_temp("owner_name", "邰玄");
        ::setup();
}
