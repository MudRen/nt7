#include <armor.h>
#include <ansi.h>

inherit MEDAL2;

void create()
{
        set_name(NOR + WHT "转世勋章（奔流）" NOR, ({ "benliu xunzhang", "benliu", "xunzhang" }));
        set("long", NOR + WHT "转世后获得的勋章，上绘万水奔流图，闪闪发亮，甚是精致。\n" NOR);
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/damage", 500);
                set("armor_prop/str", 10);
                set("armor_prop/scborn", 1);
                set("armor_prop/whip", "apply_armor() * 3");
                set("armor_prop/club", "apply_armor() * 3");
                set("armor_prop/staff", "apply_armor() * 3");
                set("armor_prop/dagger", "apply_armor() * 3");
                set("armor_prop/hammer", "apply_armor() * 3");
                set("armor_prop/axe", "apply_armor() * 3");
                set("special/desc", HIR "用莫邪圣符升级后可镶嵌提高除刀、剑外的所有兵器技能有效等级。" NOR); 
                set("limit", ([
                        "scborn" : 1, 
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}