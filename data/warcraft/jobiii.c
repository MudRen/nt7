// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m钢铁装甲[2;37;0m[2;37;0m", ({"tank"}));        
        set("gender", "男性");                
        set("long", "钢铁装甲[2;37;0m
它是打工三号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jobiii");
        set("owner_name", "打工三号");
        set_temp("owner", "jobiii");
        set_temp("owner_name", "打工三号");
        ::setup();
}
