// ITEM Made by player(唐弹:jobc) /data/item/j/jobc-noname.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Feb 13 01:01:07 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("无名指[2;37;0m", ({ "noname" }));
	set_weight(450);
	set("item_make", 1);
	set("unit", "双");
	set("long", "这是由[1;35m寒星陨铁[2;37;0m炼制而成的一双铁掌。
");
	set("makeinfo", "[1;31m
唐弹(jobc)[1;31m 出品
[2;37;0m");
	set("value", 4100000);
	set("point", 608);
	set("max_consistence", 100);
	set("material", "hanxing yuntie");
	set("material_file", "/clone/goods/hanxing-yuntie");
	set("quality_level", 2);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
