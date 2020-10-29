// ITEM Made by player(魔虎:uuu) /data/item/u/uuu-uuue.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jun 18 23:18:15 2019
#include <ansi.h>
#include <armor.h>

inherit WRISTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m虎王护腕[2;37;0m", ({ "uuue" }));
	set_weight(500);
	set("item_make", 1);
	set("unit", "对");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一对护腕。
");
	set("makeinfo", "[1;31m
魔虎(uuu)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 375);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 6);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/dp_power", 1.500000);
	set("armor_prop/avoid_busy", 5.000000);
	set("armor_prop/research_effect", 3);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
