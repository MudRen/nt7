
#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "头盔之魂" NOR, ({"head soul3", "head", "soul3"}));
        set_weight(100);

        set("long", HIM "这是一个头盔之魂。\n" NOR);
        set("unit", "个");
        set("value", 200000);
        set("no_sell", 1);

        set("type", "head");
        set("status", 3);
        set("auto_load", 1);
        
        setup();
}

