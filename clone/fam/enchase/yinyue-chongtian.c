inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "阴月·冲天" NOR, ({"yinyue chongtian", "chongtian" }));
        set_weight(900);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "块");
                set("value", 50000);
                set("enchase/name", "阴月·冲天");
                set("enchase/point", 80);
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
