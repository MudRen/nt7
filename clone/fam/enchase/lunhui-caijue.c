inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "轮回·裁决" NOR, ({"lunhui caijue","lunhui","caijue" }));
        set_weight(900);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                 set("long", HIM "轮回之苦·天之裁决。\n" NOR);
                set("unit", "块");
                set("value", 5000);
                set("enchase/name", "轮回·裁决");
                set("enchase/point", 120);
                  set("enchase/type", "all");
                set("enchase/cur_firm", 85);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
