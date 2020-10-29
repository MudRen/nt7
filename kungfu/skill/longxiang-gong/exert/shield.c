// shield.c 护体神功
//

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if (target != me)
                return notify_fail("你只能用龙象般若功来提升自己的防御力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("longxiang-gong", 1) < 60)
                return notify_fail("你的龙象般若功修为不够。\n");

        if( BUFF_D->check_buff(me, "shield") )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        msg = HIW "$N" HIW "大喝一声，眼中神光四射，"
                        "只见一股白雾蒸腾而起，笼罩了$N"
                        HIW "的全身！\n" NOR;

        data = ([
                "armor" : skill/2,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "shield",
                "attr"  : "bless",
                "name"  : "龙象般若功·护体神功",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的龙象般若功运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}
