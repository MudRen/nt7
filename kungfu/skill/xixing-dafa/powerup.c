#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if (target != me)
                return notify_fail("你只能用吸星大法来提升自己的战斗力。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的内力不够。\n");

        if( BUFF_D->check_buff(me, "powerup") ) 
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);
        msg = HIG "$N" HIG "深深呼入一口气，缓缓吐出，顿时全身真"
                        "气蒸腾，被罡劲所笼罩。\n" NOR;
                        
        data = ([
                "attack" : skill/3,
                "defense": skill/3,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "吸星大法·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的吸星大法运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}
