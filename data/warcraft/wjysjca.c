// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("座机[2;37;0m[2;37;0m", ({"zuoji"}));        
        set("gender", "男性");                
        set("long", "座机[2;37;0m
它是啊饿的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "wjysjca");
        set("owner_name", "啊饿");
        set_temp("owner", "wjysjca");
        set_temp("owner_name", "啊饿");
        ::setup();
}
