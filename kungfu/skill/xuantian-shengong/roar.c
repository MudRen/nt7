// roar.c 五雷啸

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;

        if( query("neili", me)<400 )
                return notify_fail("你的内力不够。\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("在这里不能攻击他人。\n");

        skill = me->query_skill("force");

        addn("neili", -150, me);
        me->receive_damage("qi", 10);

        me->start_busy(5);
        message_combatd(HIY "$N" HIY "深深地吸一囗气，发出一"
                        "声惊天动地的长啸！\n" NOR, me);

        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! living(ob[i]) || ob[i] == me)
                        continue;
                if( skill/2+random(skill/2)<query("con", ob[i])*2 )
                        continue;
                
                if (userp(ob[i]) && !ob[i]->die_protect(me)) 
                        continue;
                        
                damage=skill-(query("max_neili", ob[i])/10);
                if (damage > 0)
                {
                        ob[i]->receive_damage("jing", damage * 2, me);
                        if( query("neili", ob[i])<skill*2 )
                        ob[i]->receive_wound("jing", damage);
                        tell_object(ob[i], "你觉得眼前一阵金星乱冒，耳朵痛得像是要裂开一样！\n");
                }

                me->want_kill(ob[i]);
                ob[i]->kill_ob(me);
        }

        return 1;
}