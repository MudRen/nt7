#include <ansi.h>
#include <combat.h>

#define XUN "「" HIY "迅雷一击" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/xunlei-jian/xun", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(XUN "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器无法施展" XUN "。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的内功的修为不够，无法施展" XUN "。\n");

        if (me->query_skill("xunlei-jian", 1) < 100)
                return notify_fail("你的迅雷剑法修为不够，无法施展" XUN "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真气不够，无法施展" XUN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "飞身一跃而起，手中" + weapon->name() + NOR + HIY
              "一抖，剑身顿时幻作一道电光，直直射向$n" HIY "而去！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -180, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "躲避不及，剑光顿时透体而"
                                           "入，一声惨叫，鲜血狂泻不止。\n" NOR );
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "奋力格挡，终于架开了$P"
                       CYN "凌厉的剑招。 \n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}