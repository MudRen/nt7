// This program is a part of NITAN MudLIB
// ying.c 须弥山掌「群山叠影」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "群山叠影"; }

int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「群山叠影」只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能使用「群山叠影」！\n");

        if ((lvl = (int)me->query_skill("xumishan-zhang", 1)) < 150)
                return notify_fail("你的须弥山掌掌不够娴熟，不会使用「群山叠影」。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在真气太弱，不能使用「群山叠影」。\n");

        if (me->query_skill_prepared("strike") != "xumishan-zhang")
                return notify_fail("你现在没有准备使用须弥山掌，不能使用「群山叠影」。\n");

        msg = HIY "$N" HIY "稳稳使出须弥山掌掌的绝招「群山叠影」，双掌"
              "平平向$n" HIY "推去，$n" HIY "顿时觉得一股排山倒海的"
              "内力向自己涌来。\n" NOR;
        addn("neili", -150, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "顿时觉得呼吸不畅，全然被这"
                       "股力道所制，只得拼命运动抵挡。\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "深吸一口气，凝神抵挡，犹如轻舟立"
                       "于惊涛骇浪之中，左右颠簸，却是不倒。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(2);
        return 1;
}
