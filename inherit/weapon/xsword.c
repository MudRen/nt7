// xsword.c
#include <ansi.h>
#include <weapon.h>
#include <music.h>

#ifdef AS_FEATURE
#include <dbase.h>
#else
inherit EQUIP;
#endif

inherit MI_XIAO;

int is_weapon() { return 1; }

varargs void init_xsword(int damage, int flag)
{
        //if( clonep(this_object()) ) return;

        set("weapon_prop/damage", damage * 90 / 100);
        set("flag", (int)flag | EDGED | SECONDARY); 
        set("skill_type", "sword");
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
                set("verbs", ({ "slash", "slice", "thrust" }) );
        }
}

void init()
{
        add_action("play_xiao", "play");
}

string extra_long()
{
        mapping need;
        string str;

        str = HIW "\n物品类型 : 兵器(箫)\n" NOR;
        if (query("bindable"))
        {
                string type;
                int t;

                t = query("bindable");
                if (t == 1) type = "装备绑定";
                else if (t == 2) type = "拾取帮定";
                else if (t == 3) type = "直接绑定";
                str += sprintf(HIW "绑定类型 : %s\n" NOR, type);
        }
        str += sprintf(HIW "重    量 : %d\n" NOR, this_object()->query_weight());
        str += sprintf(HIW "伤 害 力 : %d\n" NOR, query("weapon_prop/damage"));
        // str += sprintf(HIW "杀    戮 : %d\n" NOR, query("combat/PKS"));
        str += sprintf(HIW "镶嵌凹槽 : %d\n" NOR, (int)query("enchase/flute"));
        if (mapp(need = query("need")) && sizeof(need))
                foreach (string key in keys(need))
                        str += sprintf(HIW "装备要求 : %s %d\n" NOR,
                                       to_chinese(key), need[key]);
        /*
        str += sprintf(HIW "使用方式 : 输入指令 wield %s 装备。\n", query("id"));
        str += sprintf(HIW "使用方式 : 输入指令 unwield %s 卸下。\n", query("id"));
        */
        str += sprintf(HIW "下线丢失 : %s\n" NOR,
                       this_object()->query_autoload() ? "否" : "是");

        return str;
}
