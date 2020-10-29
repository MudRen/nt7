#include <armor.h>
#include <ansi.h>

inherit SURCOAT;

void create()
{
        set_name(HIG "魔灵之翼" NOR, ({ "moling zhiyi", "moling", "zhiyi" }) );
        set_weight(2000);
        set("long", HIG "这是一件形似传说中怪鸟羽翼般的披风，看起来盛气逼人。\n" NOR);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("material", "steel");
                                set("value", 3000000);
                set("armor_prop/armor", 100);
                                set("armor_prop/con", 4);
                                set("armor_prop/int", 6);
                                set("armor_prop/dodge", 20);
                                set("special/desc", HIR "提升有效轻功20级。");
                                set("limit", ([ 
                                        "exp" : 9000000,
                                        "scborn" : 1,
                                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}