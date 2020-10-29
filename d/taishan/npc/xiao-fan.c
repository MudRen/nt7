// xiaofan.c
// Last Modified by Lonely on Aug. 25 2001

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("小贩", ({ "xiao fan", "seller", "fan" }) );
        set("gender", "男性" );
        set("age", 32);
        set("long", "这是个小贩，别看他长的老老实实，可你别想从他那儿掏便宜。\n");
        set("shen_type", 1);
        set("combat_exp", 1000);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "peaceful");
        set("vendor_goods", ({
                "/d/village/npc/obj/shoes",
                "/d/village/npc/obj/bottle",
        }) );
        setup();
        carry_object("clone/misc/cloth")->wear();
        add_money("coin", 100);
}
void init()
{
        ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}
