// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"fkaa"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是魏海的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wkg");
        set("owner_name", "魏海");
        set_temp("owner", "wkg");
        set_temp("owner_name", "魏海");
        ::setup();
}
