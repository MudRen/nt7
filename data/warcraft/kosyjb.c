// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m贰研[2;37;0m[2;37;0m", ({"kosyjapet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是研贰的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosyjb");
        set("owner_name", "研贰");
        set_temp("owner", "kosyjb");
        set_temp("owner_name", "研贰");
        ::setup();
}
