#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + WHT "羊皮碎片" NOR, ({ "sui pian1", "suipian1", "pian1" }));
        set_weight(300);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + WHT "这是一块羊皮碎片，上面绘有残缺不全"
                            "的九宵纹龍纹样。\n" NOR);
                set("unit", "块");
                set("value", 10);
                set("material", "paper");
        }
}

int query_autoload()
{
        return 1;
}