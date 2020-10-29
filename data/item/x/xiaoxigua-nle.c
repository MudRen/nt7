// ITEM Made by player(小西:xiaoxigua) /data/item/x/xiaoxigua-nle.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan  6 14:53:48 2019
#include <ansi.h>
#include <armor.h>

inherit HEAD;
inherit F_ITEMMAKE;

void create()
{
	set_name("内力[2;37;0m", ({ "nle" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "顶");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一顶头盔。
");
	set("makeinfo", "[1;31m
小西(xiaoxigua)[1;31m 出品
[2;37;0m");
	set("value", 36000000);
	set("point", 897);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 2);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
