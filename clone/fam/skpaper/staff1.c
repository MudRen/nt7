#include <ansi.h>

inherit __DIR__"skpaper";

void create()
{
        set_name(NOR + WHT "杖谱残篇" NOR, ({ "zhangpu canpian", "zhangpu", "canpian" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "张");
                set("long", "这是一张残缺不全的书页。\n" NOR);
                set("value", 30);
                set("no_sell", "什么世道，就一张破纸头也拿来卖钱？");
                set("material", "paper");
                set("skill_name", "基本杖法");
                set("skill_type", "staff");
                set("power_point", 30000);
                set("need_exp", 300000);
                set("min_lvl", 100);
                set("max_lvl", 300);
        }
        setup();
}