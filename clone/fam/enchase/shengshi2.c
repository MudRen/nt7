inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY "圣石" NOR, ({"god stone2", "stone2"}));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "粒");
                set("value", 500000);
                set("enchase/name", "圣石");
                set("enchase/point", 1);
                set("enchase/type", "neck");
                                set("enchase/cur_firm", 100);
                                set("nine_object", 1); // 九孔镶嵌物品标记
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
