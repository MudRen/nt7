// unarmed.c 基本拳脚
// Last Modified by Lonely on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

string type() { return "martial"; }
string martialtype() { return "skill"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

void skill_improved(object me)
{}

int help(object me)
{
        write(HIC"\n基本拳脚："NOR"\n");
        write(@HELP

    拳脚类武技的基本功，并能改善你后天的膂力。

        学习要求：
                无
HELP
        );
        return 1;
}
