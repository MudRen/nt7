// advance_force.c

inherit ITEM;

void create()
{
        set_name("内功详解", ({ "force book", "book" }));
        set_weight(600);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "本");
                set("long",
"封面上写著「内功详解）」\n");
                set("value", 10000);
                set("material", "paper");
                set("skill", ([
                        "name":         "force",
                        "exp_required": 1000,
                        "jing_cost":    30,
                        "difficulty":   30,
                        "max_skill":    99,
                        "min_skill":    50,
                ]));
        }
}

int is_yaowang_book() { return 1; }