#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIG "翡翠绿" NOR, ({ "emerald" }));
        set_name(HIG "翡翠绿石头" NOR, ({ "emerald" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", WHT "这是一颗宝石，上面似乎附着某种神奇的魔力。\n" NOR);
                set("value", 100000);
                set("unit", "颗");
                set("material", "emerald"); 
                set("no_identify", 1);
        }
        setup();
}
