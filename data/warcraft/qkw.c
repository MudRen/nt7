// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"fkaa"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是曲夜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qkw");
        set("owner_name", "曲夜");
        set_temp("owner", "qkw");
        set_temp("owner_name", "曲夜");
        ::setup();
}
