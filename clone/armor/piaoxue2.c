#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIW "飘雪" NOR, ({ "piao xue2", "piao", "xue2" }));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "根");
                set("value", 400000);
                                set("special/desc", HIW "额外提高有效轻功20级。" NOR);
                                set("armor_prop/dex", 20);
                                set("armor_prop/str", -7);
                set("armor_prop/dodge", 20);
                                set("limit", ([ 
                                        "exp" : 9000000,
                                        "dex" : 50, 
                                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}