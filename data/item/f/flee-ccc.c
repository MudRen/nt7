// ITEM Made by player(桃枝妖妖:flee) /data/item/f/flee-ccc.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan 30 01:53:15 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;37m蕾丝胸[2;37;0m", ({ "ccc" }));
	set_weight(2000);
	set("item_make", 1);
	set("unit", "件");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一件战衣。
");
	set("makeinfo", "[1;31m
桃枝妖妖(flee)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 1500);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 4);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/max_experience", 40000);
	set("armor_prop/research_effect", 2);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
