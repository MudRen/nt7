//bagua1.c

inherit ITEM;
inherit F_UNIQUE;
#include <ansi.h>
 
void create()
{
        set_name(HIC"「洛书」"NOR, ({ "luoshu","shu", }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long","这是一本用薄绢写成的书。上书二字古篆：“洛书”。\n书皮泛黄，看来已经保存很久了。\n" );
                set("value", 0);
                set("material", "silk");
                set("skill", ([
                        "name":       "count",
                        "jing_cost":  40,
                        "difficulty": 30,
                        "max_skill":  149,
                        "min_skill":  100
                ]) );
        }
}