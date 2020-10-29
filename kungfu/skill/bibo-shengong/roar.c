// roar.c 
// by Lonely

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;

        if( query("neili", me)<600
        ||  (int)me->query_skill("bibo-shengong", 1) < 50)
                return notify_fail("你鼓足真气「喵」的叫了一声, 结果吓走了几只老鼠。\n");
                
        skill = me->query_skill("force", 1) / 4 + me->query_skill("bibo-shengong", 1);
        addn("neili", -150, me);
        me->receive_damage("qi", 10);
        
        if( query("no_fight", environment(me)) )
                return notify_fail("这里不能攻击别人! \n");

        me->start_busy(5);
        message_combatd(HIY "$N" HIY "气凝丹田，运集全身内力吟出" 
                        "一曲「碧海生潮」远远的传了开去，激荡不止！\n" NOR, me); 
        
        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++) 
        {
                if (! ob[i]->is_character() || ob[i] == me)
                        continue;
                        
                if (! living(ob[i]) || wizardp(ob[i]) || 
                    (query("age", ob[i])<17 && userp(ob[i])) )
                        continue;
                        
                if (userp(ob[i]) && ! ob[i]->die_protect(me))
                        continue;
                        
                if (skill / 2 + random(skill / 2) < (int)ob[i]->query_skill("force"))
                        continue;
 
                me->want_kill(ob[i]);
                me->fight_ob(ob[i]);
                ob[i]->kill_ob(me);
                      
                damage=skill-(query("max_neili", ob[i])/30);
                if (damage > 0) 
                {
                        set("last_damage_from", me, ob[i]);
                        ob[i]->receive_damage("jing", damage * 2, me );
                        if( query("neili", ob[i])<skill*2 )
                                ob[i]->receive_wound("jing", damage, me);
                        tell_object(ob[i], "你只觉得眼前一片模糊，朦胧" 
                                    "中似乎无数排山巨浪向你打来......\n"); 
                }
        }
        return 1;
}