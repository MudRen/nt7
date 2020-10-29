// zhenyu.c 镇狱惊天丸

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "镇狱惊天丸" NOR, ({ "zhenyu wan", "zhenyu", "wan" }) );
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "一颗龙眼大小的药丸，氤氲扑鼻，一嗅之下便觉心旷\n"
                                "神怡。整个药丸流动着金属般的光泽，入手沉重，在\n"
                                "掌心滑动不停，便似有生命一般。\n"
                                "本物品第一次吃效果最佳！\n" NOR);
                set("value", 500000);
                set("no_sell", 1);
                set("unit", "颗");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        string mapsk;
        int effect;
        int neili;

        log_file("static/using", sprintf("%s(%s) eat 镇狱惊天丸 at %s.\n",
                 me->name(1),query("id", me),ctime(time())));

        effect = 0;

        if( query("skybook/item/zhenyu", me) )
        {
                /*
                message_vision(HIR "$N" HIR "一仰脖，吞下了一颗镇狱惊天丸，却听$P"
                               HIR "一声尖哮，喷出一口鲜血。\n" NOR, me);

                me->set_temp("die_reason","贪吃镇狱惊天丸，结果弄得全身筋脉尽断"
                                           "而亡");
                me->die();
                */ 
                me->improve_neili(800);
                me->improve_jingli(500);
                addn("skybook/item/zhenyu", 1, me);
                message_vision(HIW "$N" HIW "一仰脖，吞下了一颗镇狱惊天丸，只见$P"
                               HIW "浑身一颤，七窍都冒出白烟来。\n" NOR, me);
        } else
        {
                message_vision(HIW "$N" HIW "一仰脖，吞下了一颗镇狱惊天丸，只见$P"
                               HIW "浑身一颤，七窍都冒出白烟来。\n" NOR, me);

                //addn("combat_exp", 2000000+random(1000000), me);
                addn("magic_points", 3000, me);
                addn("potential", 30000, me);

                mapsk = me->query_skill_mapped("force");
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);

                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);

                me->improve_neili(800);
                me->improve_jingli(500);
                addn("skybook/item/zhenyu", 1, me);
        }
        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}