inherit NPC;

void create()
{
        set_name("男子", ({ "man", "nan zi" }) );
        set("gender", "男性" );
        set("age", 23);
        set("shen_type", 1);
        set("combat_exp", 10000);
        set("str", 20);
        set("dex", 20);
        set("con", 20);
        set("int", 20);
        set("attitude", "peaceful");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}
