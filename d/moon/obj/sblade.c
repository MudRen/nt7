// xueblade.c

#include <weapon.h>
#include <ansi.h>
inherit BLADE;

void create()
{
	set_name("短刀", ({ "blade" }) );
	set_weight(800);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("value", 1000);
		set("material", "iron");
		set("long", "这是一把锋利无比的钢刀。\n");
		set("wield_msg", " $N抽出一把锋利的$n握在手中。\n");
		set("unequip_msg", "$N放下手中的$n。\n");
	}
	init_blade(30);
	setup();
}