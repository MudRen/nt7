// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m贰武[2;37;0m[2;37;0m", ({"matipet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是武贰的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mati");
        set("owner_name", "武贰");
        set_temp("owner", "mati");
        set_temp("owner_name", "武贰");
        ::setup();
}
