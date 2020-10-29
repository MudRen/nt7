
// upblood
/*
血脉分为十级：觉醒 通脉 易筋 洗髓 换骨 脱胎 灵身 仙体 神脉 圣尊
血脉的修炼需要材料如下：
    觉醒：每次消耗一颗血脉丹（一品），修炼一次增加进度5%
    通脉：每次消耗一颗血脉丹（二品），修炼一次增加进度5%
    易筋：每次消耗一颗血脉丹（三品），修炼一次增加进度5%
    洗髓：每次消耗一颗血脉丹（四品），修炼一次增加进度5%
    换骨：每次消耗一颗血脉丹（五品），修炼一次增加进度4%
    脱胎：每次消耗一颗血脉丹（六品），修炼一次增加进度4%
    灵身：每次消耗一颗血脉丹（七品），修炼一次增加进度4%
    仙体：每次消耗一颗血脉丹（八品），修炼一次增加进度3%
    神脉：每次消耗一颗血脉丹（九品），修炼一次增加进度3%
    圣尊：每次消耗一颗血脉丹（十品），修炼一次增加进度3%
攻击技能·天怒神罚，代天行罚
    血脉修炼完成第一重“觉醒”，自动领悟主动攻击技能——“天怒神罚”。
血脉等级的提高可大幅度提高玩家的最大内力、最大精力上限，同时大幅度提高玩家的最大气血和精气，以及攻击力和防御力。
*/

#include <ansi.h>

inherit F_CLEAN_UP;

int help(object me);
mapping xuemai = ([
        "stealth" : "仙体",
        "wisdom"  : "人体",
        "ghost"   : "鬼体",
        "demon"   : "魔体",
        "nopoison": "怪体",
        "monster" : "妖体",
]);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int points, added, level, i;
        mapping my, spe_data;
        string msg, skill, sname;
        object dan;
        string *spe_skill = ({
                "monster", "nopoison", "demon", "ghost", "wisdom", "stealth",
        });
                
        seteuid(getuid());
 
        if( me->is_busy() || me->is_fighting() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg || arg == "" )
                return help(me);
        
        if( arg == "reset" )
        {
                delete("xuemai_level", me);
                delete("xuemai", me);
                delete("xuemai_skill", me);
                for( i=0; i<sizeof(spe_skill); i++ )
                {
                        if( query("special_skill/"+spe_skill[i], me) )
                                delete("special_skill/"+spe_skill[i], me);
                }
                write(HIR "你取消了你的血脉传承属性。\n" NOR);
                return 1;
        }
        
        if( arg == "check" )
        {
        	if( query("xuemai_skill",me) )
                {
                write(HIR "你的血脉传承属性是："+ xuemai[query("xuemai_skill",me)] +"。\n" NOR);
                return 1;
            }
            return notify_fail("你当前没有血脉属性。\n");
        }
        
        
        
        
        if( !objectp(dan = present(arg, me)) )
                return notify_fail("你身上没有血脉丹，无法提升血脉。\n");
                
        if( !dan->is_xuemai_dan() )
                return notify_fail("你无法使用它来提升血脉。\n");
        
        level = query("xuemai_level", me) + 1;
        if( level > 10 )
                return notify_fail("你的血脉已经达到最高境界了，无需继续提升了。\n");
        
        if( query("level", dan) < level )
                return notify_fail("你身上的血脉丹品级过低，无法提升血脉。\n");
        
        if( !query("jingmai/finish", me) )
                return notify_fail("你需要先打通你全身大小周天经脉。\n");
                                      
        if( (int)me->query_skill("force", 1) < 2000 )
                return notify_fail("你的内功修为不足，没法提升自身血脉。\n");

        if( query("potential", me)-query("learned_points", me) < 10000000 )
                return notify_fail("你的潜能不够，没法提升自身血脉。\n");
        
        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("你现在的气太少了，无法静心提升血脉。\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("你现在的精太少了，无法静心提升血脉。\n");

        if( query("max_neili", me) < 100000 )
                return notify_fail("你觉得内力颇有不足，看来目前还难以进行血脉的提升。\n");

        if( query("neili", me)*100/query("max_neili", me) < 90 )
                return notify_fail("你现在的内力太少了，无法静心提升血脉。\n");

        addn("learned_points", 10000000, me);
        dan->add_amount(-1);
        if( dan->query_amount() < 1 )  
                destruct(dan);  
                
        message_vision(HIW "只见$N" HIW "头上白雾腾腾、浑身如同笼罩在云中。\n" NOR, me);
        
        //全身血液焕然一新，所谓是练髓如霜，练血汞浆。脱胎换骨，伐毛洗髓。
        
        switch (level)
        {
        case 1:
                msg = HIR "你周身血液宛如火焰一样炽热，血液翻滚着。血脉中一些奇特的东西正在逐渐的苏醒，你感受到了\n"
                      "一种前所未有的强横力量正逐渐的从你身体每一个角落浸润出来。\n" NOR;
                break;

        case 2:
        case 3:
        case 4:
                msg = HIB "你的血液被冻结了，然后变成了流动的冰霜，迅速的冲刷着你的身体。从骨髓到皮肤，大量的污垢\n"
                      "杂质不断的被暴力排斥出来。你的骨髓逐渐的转变着颜色，变得更加润红，更加的深邃。\n" NOR;
                break;

        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
                msg = HIR "你的血液开始沸腾，你的骨髓中开始不断产生巨量的血液，而这些血液中的细胞开始疯狂的吞噬和\n"
                      "合并，大量奇妙的气息从你的血液中不断的滋生，渐渐的你的血液变得越来越粘稠，每一滴血液中\n"
                      "蕴藏的能量和营养越来越强大，光泽也越来越夺目瑰丽。\n" NOR;
                break;

        default:
                msg = HIY "你原本红色的血液，已经彻底转化为淡金色。如果将你的血液盛放在容器中，那将会是一颗淡金色\n"
                      "的宝珠，因为本体蕴藏的庞大能量不断外泄，这颗宝珠如果不加以控制，它将会满天乱飞，并且因\n"
                      "为它庞大的密度而对四周的物体造成可怕的破坏，甚至空间塌陷。\n" NOR;
                break;
        }

        tell_object(me, msg);
                
        points = query("xuemai/points", me);
        
        if( level < 5 ) added = 5;
        else if( level < 8) added = 4;
        else added = 3;
        
        points += added;
        set("xuemai/points", points, me);
        
        if( points >= 100 )
        {
                addn("xuemai_level", 1, me);
                delete("xuemai/points", me);
                
                
                if( query("xuemai_level", me) == 1 )
                {
                        skill = spe_skill[random(sizeof(spe_skill))];
                        set("xuemai_skill", skill, me);
                        tell_object(me, HIM "你终于唤醒了你的远古血脉传承-->"+xuemai[skill]+"。\n" NOR);
                        tell_object(me, HIC "你如果对血脉传承属性不满意，可以upblood reset来重新获取血脉传承。\n" NOR);
                }
                else if( query("xuemai_level", me) == 10 )
                {
                        // 取消原先元神获得的血脉技能
                        for( i=0; i<sizeof(spe_skill); i++ )
                        {
                                if( query("special_skill/"+spe_skill[i], me) )
                                        delete("special_skill/"+spe_skill[i], me);
                        }
                        my = me->query_entire_dbase();
                        skill = query("xuemai_skill", me);
                        sname = SPECIAL_D(skill)->name();
                        
                        spe_data = ([ skill : 1 ]);                                              
                        my["special_skill"] += spe_data;

                        tell_object(me, HIM "你成功的激活了血脉力量，掌握了血脉技能-->"+sname+"。\n" NOR);
                }
                else
                        tell_object(me, HIM "你的血脉等级（品级）提升了。\n" NOR);

                CHAR_D->setup_char(me); 
        }

        me->start_busy(1);
        return 1;
}


int help(object me)
{
        write(@HELP
指令格式 : upblood <xuemai dan1> 提升血脉的品级
           upblood reset         重新觉醒血脉传承
           upblood check         查询你的当前血脉属性

修炼提升血脉的等级，唤醒血脉技能。

HELP );
        return 1;
}

