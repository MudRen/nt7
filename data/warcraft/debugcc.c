// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuquecc"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是姓名三米的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "debugcc");
        set("owner_name", "姓名三米");
        set_temp("owner", "debugcc");
        set_temp("owner_name", "姓名三米");
        ::setup();
}
