// diyun 狄云

inherit NPC;

void create()
{
        set_name("狄云", ({ "di yun", "diyun"}));
        set("long", "他英武刚正，有一股豪迈之气。\n");
        set("gender", "男性");
        set("age", 25);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 20);

        setup();
        carry_object("/clone/cloth/cloth.c")->wear();
}