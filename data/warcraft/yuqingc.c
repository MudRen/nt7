// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "鸟类的一种。[2;37;0m
它是仓丸的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yuqingc");
        set("owner_name", "仓丸");
        set_temp("owner", "yuqingc");
        set_temp("owner_name", "仓丸");
        ::setup();
}
