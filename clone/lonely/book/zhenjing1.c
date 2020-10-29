#include <ansi.h>; 
inherit ITEM;

void create()
{
        set_name(WHT "「九阴真经」上册" NOR, ({ "zhenjing shangce", "shangce", "zhenjing", "jing"}));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", 1);
                set("long", WHT "\n这是一本用薄纸写成的书，封皮上写有「九阴真经」上\n"
                            "册六字。书皮泛黄，看来已经保存很久了。真经中记载\n"
                            "有大伏魔拳、易筋锻骨和蛇行狸翻等绝技，你可以试着\n"
                            "读读(read)看。\n\n" NOR, );
        }
}

void init()
{
        add_action("do_du", "read");
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;

        string skill, book;
        int lv;

        if (! arg)
        {
                write("研读九阴真经指令格式：read <技能> from <九阴真经>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", skill, book) != 2)
        {
                write("研读九阴真经指令格式：read <技能> from <九阴真经>\n");
                return 1;
        }

        if (me->is_busy())
        {
                write("你现在正忙着呢。\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("你无法在战斗中专心下来研读新知！\n");
                return 1;
        }

        if( query("no_fight", where )
            && query("doing", me) != "scheme" )
        {
                write("你无法在这里静下心来研读真经。\n");
                return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("你是个文盲，先学点文化(literate)吧。\n");
                return 1;
        }

        if (! id(book))
        {
                write("这里没有这本书。\n");
                return 1;
        }

        if (skill != "yijin-duangu" && skill != "易筋锻骨"
           && skill != "shexing-lifan" && skill != "蛇行狸翻"
           && skill != "dafumo-quan" && skill != "大伏魔拳")
        {
                write("真经上并没有记载你打算研究的内容。\n" NOR);
                return 1;
        }

        if (me->query_skill("sanscrit", 1) < 200)
        {
                write("你的梵文水平太低，无法看懂真经里所记载的内容。\n");        
                return 1;
        }

        if( query("combat_exp", me) < 800000 )
        {
                write("你的实战经验不足，再怎么读也没用。\n");
                return 1;
        }

        if( query("jing", me)<100
            || query("qi", me)<100
            || query("neili", me)<200 )
        {
                write("你现在过于疲倦，无法专心下来研读新知。\n");
                return 1;
        }

        if (skill == "yijin-duangu" || skill == "易筋锻骨")
                skill = "yijin-duangu";
        else

        if (skill == "shexing-lifan" || skill == "蛇行狸翻")
                skill = "shexing-lifan";
        else

        if (skill == "dafumo-quan" || skill == "大伏魔拳")
                skill = "dafumo-quan";

        if (! SKILL_D(skill)->valid_learn(me))
                       return 0;

        if (! me->can_improve_skill(skill))
               {
                       write("你的实战经验不足，再怎么读也没用。\n");
                       return 1;
               }

        lv = me->query_skill(skill, 1);

        if (lv >= 180)
        {
                write("你研读了一会儿，但是发现上面所说的对你而言都太浅了。\n");
                return 1;
        }

        // 天赋聪颖增加研读速度
        if( query("special_skill/clever", me) )
                me->improve_skill(skill,query("int", me)+5);
        else
                me->improve_skill(skill,query("int", me)+1);

        me->receive_damage("qi", random(50) + 30);
        me->receive_damage("jing", random(50) + 30);
        addn("neili", -lv, me);
        message("vision", me->name() + "正专心地研读九阴真经。\n",
                          environment(me), me);
        write("你仔细研读九阴真经，颇有心得。\n");
        return 1;
}
