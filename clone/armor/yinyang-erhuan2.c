#include <armor.h>
#include <ansi.h>

inherit EARRING;

void create()
{
        set_name(HIW "阴阳耳环" NOR, ({ "yinyang erhuan2", "yinyang", "erhuan2" }));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "副");
                set("value", 200000);
                set("material", "silver");
                set("armor_prop/armor", 1);
                set("armor_prop/force", 30);
                set("armor_prop/con", 6);
                set("limit", ([
                        "sex" : 3, // 1 为无性
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}