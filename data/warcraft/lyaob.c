// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白虎[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是炼药乙的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lyaob");
        set("owner_name", "炼药乙");
        set_temp("owner", "lyaob");
        set_temp("owner_name", "炼药乙");
        ::setup();
}
