// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "居家旅行必备之物。[2;37;0m
它是魔首领的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mpurena");
        set("owner_name", "魔首领");
        set_temp("owner", "mpurena");
        set_temp("owner_name", "魔首领");
        ::setup();
}
