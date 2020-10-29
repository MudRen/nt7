// ganjiang.c  干将
// Written by Doing Lu  1998/11/2
// Updated by Lonely@nitan.org

// 干将负责炼道具的场景，但是不接受玩家的物品，玩家如果炼制
// 道具应该和莫邪打交道。如果 player 在莫邪那里将一切手续办
// 妥，莫邪将原料交给干将。通过accept_object 函数启动干将的
// 炼制程序。

// 干将接收到莫邪传来的道具，则对他进行锻炼，锻炼完以后，设
// 设置道具的铸造者，铸造者的ID，不设置道具的有效点数 point，
// 因为在莫邪那里已经设置了。并且等候 player 输入关于道具的
// 信息，如果超时，就清除三人的标志，并解除object。如果用户
// finish，这询问 player 是否决定，如果是则生成道具文件，并
// 在生成道具送给 player，否则继续修改。

inherit NPC;
inherit F_NOCLONE;

#include <ansi.h>

//强化的装备需要的元素，调整为 只要 七彩元素，装备分解为七彩元素，就是元素只有7种了，不对应属性

// 如果字符串被设置成这个值，表示输入的字符串具有非法的格式
#define ILLEGAL_STR     "."
// 在convert时看看要不要去掉彩色
#define NOCOLOR         1
#define COLORABLE       0

protected int   ask_certosina();
protected int   ask_enchanting();
protected int   ask_me();                               // 显示定做信息
protected int   show_order();                           // 显示规则信息
protected int   start_work(object me, object ob);       // 开始工作
protected int   prepare_make(object me, object ob);     // 开始打造
protected int   do_show(string arg);
protected int   do_notch(string arg);                   // 道具开槽
protected int   start_make(object me, object ob);       // 装备签名
protected void  clear_data();                           // 清除 ganjiang, moye, player 的临时变量并去除粗坯对象
protected string  create_file(object item_temp);
protected int     save_item_file(string filename, string content);
protected void    tell_rules(object me);
protected void    waiting(object me, object ob, object moye);
protected string  converts(string arg, int max_len, int nocolor);
protected string  prop_segment(mapping p, string path);
protected int     save_item_file(string filename, string content);
protected int     legal_chinese(string str);

mapping rings_sockets = ([
        "1" : ({"rune05","rune12","rune18"}),
        "2" : ({"rune06","rune13","rune19"}),
        "3" : ({"rune07","rune14","rune20"}),
]);

mapping equip_sockets = ([
        "1" : ({"rune01","rune06","rune15"}),
        "2" : ({"rune02","rune07","rune16"}),
        "3" : ({"rune03","rune08","rune17"}),
        "4" : ({"rune04","rune09","rune18"}),
        "5" : ({"rune05","rune10","rune19"}),
        "6" : ({"rune06","rune11","rune20"}),
        "7" : ({"rune07","rune12","rune21"}),
]);

mapping qianghua_rune = ([
        "0" : "rune25",
        "1" : "rune26",
        "2" : "rune27",
        "3" : "rune28",
        "4" : "rune29",
        "5" : "rune30",
        "6" : "rune31",
        "7" : "rune32",
        "8" : "rune33",
]);

mapping suit_level = ([
        "1" : HIC"大道"NOR,
        "2" : HIB"通玄"NOR,
        "3" : HIM"鸿钧"NOR,
        //"4" : HIM"混沌"NOR,
        "4" : HIY"造化"NOR,
]);

void create()
{
        seteuid(getuid());

        set_name("干将", ({ "gan jiang", "ganjiang", "gan" }));
        set("long", "他长得粗壮有力，脸庞似如刀削，透出一股英气。他是古往今来有名的铸剑大师。\n" );

        set("nickname", HIR "剑师" NOR);
        set("gender", "男性");
        set("attitude", "friendly");

        set("age", 1535);
        set("shen_type", 0);

        set("str", 1000);

        set("inquiry", ([

                "炼制" : (: ask_me :),
                "练剑" : (: ask_me :),
                "炼剑" : (: ask_me :),
                "铸剑" : (: ask_me :),
                "打造" : (: ask_me :),
                "铸造" : (: ask_me :),
                "制造" : (: ask_me :),
                "打制" : (: ask_me :),
                "定制" : (: ask_me :),
                "定做" : (: ask_me :),
                "定造" : (: ask_me :),
                "兵器" : (: ask_me :),
                "道具" : (: ask_me :),
                "装备" : (: ask_me :),
                "武器" : (: ask_me :),
                "刀剑" : (: ask_me :),
                "装甲" : (: ask_me :),
                
                "开槽" : "我只给神兵利器开槽打孔(notch)，寻常刀剑防具莫提，备好开槽的所需符文，费用一千两黄金将从银行扣除。\n",
                "打孔" : "我只给神兵利器开槽打孔(notch)，寻常刀剑防具莫提，备好开槽的所需符文，费用一千两黄金将从银行扣除。\n",
                "原料" : "炼剑就得有原料，一分钱，一分货，好原料就能出好东西。\n",
                "定金" : "定金少得很，才五两黄金，要交定金请交给莫邪。\n",
                "价格" : "一分钱一分货......",
                "销毁" : "那就...退回(discard)来吧...",
                "退货" : "那就...退回(discard)来吧...",

                "规则" : (: show_order :),
                "方法" : (: show_order :),
                "order": (: show_order :),

                //"强化"    : "想要知道强化装备需要的材料，请show <装备>，我会告诉你所需的材料。\n",
                //"强化装备": "想要知道强化装备需要的材料，请show <装备>，我会告诉你所需的材料。\n",
                "兑换超能力水晶":"想要超能力水晶，请show <装备>，我会帮你熔炼制成超能力水晶。\n",
                "镶嵌"    : (: ask_certosina :),
                "镶嵌技术": (: ask_certosina :),
                "镶嵌技艺": (: ask_certosina :),
                "certosina": (: ask_certosina :),
                "附魔技艺": (: ask_enchanting :),
                "附魔技术": (: ask_enchanting :),
                "enchanting": (: ask_enchanting :),
                "套装"    : "绿化套装必须要有王者之心，如果给我王者之心的话，我就帮你绿化(dosuit <装备>)套装。",
                "升级套装": "升级套装必须要有鸿蒙灵气，指令格式upsuit <装备>",
        ]));

        set_skill("literate",  600);            // 读书写字
        set_skill("forging",   2000);            // 锻造技巧
        set_skill("smelting",  2000);            // 冶炼技艺
        set_skill("certosina", 2000);            // 镶嵌技艺
        set_skill("enchanting", 2000);            // 附魔技艺

        set("no_teach", ([
                "literate" : "我可不是教书先生。",
        ]));

        setup();

        set("startroom", "/d/item/xiaowu");
        check_clone();
        if (! this_object()) return;

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_name", "name");
        add_action("do_name", "命名");
        add_action("do_desc", "desc");
        add_action("do_desc", "描述");
        //add_action("do_level", "level");
        //add_action("do_level", "等级");
        add_action("do_wieldmsg", "wieldmsg");
        add_action("do_wieldmsg", "wearmsg");
        add_action("do_wieldmsg", "装备");
        add_action("do_wieldmsg", "装备信息");
        add_action("do_unwield", "unwieldmsg");
        add_action("do_unwield", "removemsg");
        add_action("do_unwield", "收起");
        add_action("do_unwield", "收起信息");
        add_action("do_finish", "finish");
        add_action("do_finish", "完成");

        add_action("do_increase", "qianghua"); // 强化装备
        add_action("do_suit", "dosuit"); // 套装套化
        add_action("do_upsuit", "upsuit"); // 套装升级

        add_action("do_help", "help");
        add_action("do_help", "帮助");

        add_action("do_restore", "rest");
        add_action("do_notch", "notch"); // 开槽
        add_action("do_merge", "merge"); // 品质打磨
        add_action("do_discard", "discard"); // 销毁

        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/ganjiang"); 
}

// 发出提示信息
protected int ask_me()
{
        message_vision("干将对$N说道：这些事请问莫邪，我只管炼剑。\n", this_player());
        return 1;
}

// 认证学习
int recognize_apprentice(object me)
{
        if( !query_temp("learnd_from/干将", me) )
        {
                message_vision("干将对$N说：好，你既然有心学，我就"
                               "教你一点吧。\n", me);
                set_temp("learnd_from/干将", 1, me);
        }
        return 1;
}

// 回答有关镶嵌技艺的信息
protected int ask_certosina()
{
        message_sort("干将对$N说道：我这里不受理镶嵌的活儿，"
                     "不过你有兴趣的话，我可以教你一点镶嵌的"
                     "技术。\n", this_player());
        return 1;
}

protected int ask_enchanting()
{
        message_sort("干将对$N说道：我这里不受理附魔的活儿，"
                     "不过你有兴趣的话，我可以教你一点附魔的"
                     "技术。\n", this_player());
        return 1;
}
        
int accept_object(object me, object ob)
{
        if( query_temp("item") ) return notify_fail("干将正忙着呢，稍等会。\n");
        
        if( me->name(1) == "莫邪" )
        {
                if( query("id", me) != "mo ye" )
                {
                        command("kick "+query("id", me));
                        message_vision("$N嘿嘿的奸笑了两声，对$n说道："
                                       "你以为取了我妻子的名字就能蒙蔽"
                                       "我？我还没瞎呢！\n",
                                       this_object(), me);
                        return 1;
                }
                start_work(query("item/owner", ob),ob);
                return 1;
        }
        
        if( query("item_origin", ob) )
        {
                message_vision("干将对$N说：你别给我这东西，把这个先交"
                               "给莫邪，在她那里付了钱再说。\n", me);
                return 0;
        } 
        else if( ob->is_item_make() )
        {
                if( ob->item_owner() != query("id", me) )
                {
                        command("heng");
                        command("say 这是你的东西吗？没收了！");
                        destruct(ob);
                        return 1;
                }
                message_vision("$N疑惑的望着$n道：“你是嫌它"
                               "不好么？那就退掉(discard)吧！”\n",
                               this_object(), me);
                return 0;
        }
        else if( query("id", ob) == "ability2 crystal" && query("upsuit_level", ob) )
        {
                message_vision("干将对$N说：超能力水晶不用给我，我可以帮你绿化套装(dosuit)，你想"
                               "绿化套装什么道具？\n", me);
                set_temp("paid/dosuit", 1, me);
                return 0;
        }       
        else if( query("id", ob) == "wangzhe zhixin" )
        {
                message_vision("干将对$N说：有了王者之心，自造装备就可以绿化套装了(dosuit)，你想"
                               "绿化套装什么道具？\n", me);
                set_temp("paid/dosuit", 1, me);
                destruct(ob);
                return 1;
        }

        message_vision("干将冷冷的对$N说道：你给我这些东西干什"
                       "么？我炼剑，不用这些东西。\n", me);
        return 0;
}

protected int start_work(object me, object ob)
{
        remove_call_out("prepare_make");
        call_out("prepare_make", 1, me, ob);
        set_temp("item/making", ob);
        set_temp("item/player", me);
        set_temp("item/status", "waiting", me);
        return 1;
}

protected int prepare_make(object me, object ob)
{
        message_vision(HIC "\n$N说道：好，开炉锻炼！\n\n" NOR, this_object());
        message_vision(HIM "$N接过莫邪手中的" + ob->name() +
                       HIM "，随手把它抛入炉内，霎时间，那" + ob->name() +
                       HIM "已被火炉中的熊熊" HIR "烈焰" HIM "吞没。\n" +
                       "$N凝视着炉火，喃喃说道：天地之精华为其血脉，日"
                       "月之光辉是其灵气......\n\n" NOR , this_object());
        remove_call_out("work_step_1");
        call_out("work_step_1", 5, me, ob);
        return 1;
}

protected int work_step_1(object me, object ob)
{
        message_vision(HIG "炉火渐渐的转成了绿色，火苗不断跳跃，你觉得屋"
                       "内十分燥热，可是干将莫邪若无其事。\n\n" NOR, this_object());

        if (objectp(me) && environment(me) == environment())
        {
                if( query("id", ob) != "no name2" )
                {
                        set_temp("item/can_help", 1, me);
                        message_vision(HIW "$N对$n说道：如果你想炼得更好，需"
                               "要注入自己的精气血脉，如是你有此意，请"
                               "助(help)我一臂之力！\n\n", this_object(), me);
                }
        }
        remove_call_out("work_step_2");
        call_out("work_step_2", 6, me, ob);
        return 1;
}

protected int work_step_2(object me, object ob)
{
        message_vision(RED "炉火淡淡的暗了下来，呈现出一片红色......\n\n" NOR, this_object());
        remove_call_out("work_step_3");
        if (objectp(me))
                delete_temp("item/can_help", me);
        call_out("work_step_3", 3, me, ob);
        return 1;
}

protected int work_step_3(object me, object ob)
{
        message_vision(HIW "$N左手持蛟龙剪，一扬手已经取出了" + ob->name() +
                       HIW "，右手持金刚锤聚精会神地用力锤打，\n渐渐的，" + ob->name() +
                       HIW"在干将手下的成了"+query("item/ctype", ob)+
                       HIW "的形状。\n\n" NOR, this_object());
        remove_call_out("work_step_4");
        call_out("work_step_4", 5, me, ob);
        return 1;
}

protected int work_step_4(object me, object ob)
{
        message_vision(HIC"$N锤打完毕，大喝一声，将"+query("item/ctype", ob)+
                       HIC "抛入水池，只听丝丝作响，从水池腾起一股雾气，"
                       "弥漫四周。\n\n" NOR, this_object());
        remove_call_out("work_step_5");
        call_out("work_step_5", 3, me, ob);
        return 1;
}

protected int work_step_5(object me, object ob)
{
        message_vision(HIW"$N缓缓的从水池抽出了炼好的"+query("item/ctype", ob)+
                       HIW "看了看，满意地说，很好，很好。\n\n" NOR,
                       this_object());
        remove_call_out("work_step_6");
        call_out("work_step_6", 2, me, ob);
}

protected int work_step_6(object me, object ob)
{
        object moye;

        if (! objectp(moye = present("mo ye")))
        {
                message_vision(HIW "干将看了看四周，说道：咦，莫邪呢？"
                               "算了算了，不做了，去吧！\n"
                               "干将把炼好的道具抛进火炉，就此不见。\n\n" NOR,
                               this_object());
                if (objectp(me))
                        delete_temp("item", me);

                if (objectp(ob) && present(ob, this_object()))
                        destruct(ob);

                delete_temp("item");
                return 1;
        }

        if (! objectp(me))
                me = find_player(query("item/owner_id", ob));

        if (! objectp(me) || environment(me) != environment())
        {
                message_vision(HIW "$N叹了口气，说道：客人为何这就去"
                               "了！？罢了罢了，不做了，去吧！\n"
                               "$N把炼好的道具抛进火炉，就此不见。\n\n" NOR,
                               this_object());
                if (objectp(me))
                        delete_temp("item", me);

                if (objectp(ob) && present(ob, this_object()))
                        destruct(ob);

                delete_temp("item");
                delete_temp("item", moye);
                return 1;
        }
        set_temp("item/status", "waiting", moye); 
        set_temp("item/status", "inputing", me); 
        message_vision("$N对$n说道：一"+query("item/unit", ob)+"好"+
                       query("item/ctype", ob)+NOR"不能没有名字，你给它起个名字吧！\n",
                       this_object(), me);

        tell_rules(me);

        // 清除道具的名字，ID，和其它属性，并且设置道具的价值和制造者
        set("item/long", "", ob);
        set("item/wield_msg", "", ob);
        set("item/wear_msg", "", ob);
        set("item/unwield_msg", "", ob);
        set("item/remove_msg", "", ob);
        set("item/owner_name",query("name",  me), ob);
        set("item/owner_id",query("id",  me), ob);

        // 设置等待时间，最多3次
        set_temp("item/waited", 4);

        // 如果超时，提醒输入
        remove_call_out("waiting");
        call_out("waiting", 300, me, ob, moye);
        return 1;
}

// 以内力哺育炉火，提高道具等级
// 要求：精 >= 180  气 >= 300  内力有效等级 >= 100  内力 >= 800 最大内力 >= 1000
// 结果：耗费 200 点内力，可以提高 10%
int do_help(string arg)
{
        object me;
        object ob;
        int lvl;

        me = this_player();
        if( query_temp("item/status", me) != "waiting" )
        {
                return notify_fail("没你什么业务。\n");
        }
        if( !query_temp("item/can_help", me) )
        {
                if (arg) return 0;
                write("现在不是你帮忙的时候！\n", me);
                return 1;
        }
        if( query("jing", me)<180 )
        {
                message_vision(HIR "$N" HIR "长啸一声，双手搭上炉边，正待以内"
                               "力哺育炉火，突然眼前一黑...\n" NOR, me);
                tell_object(me, RED "你感到精力衰竭。\n" NOR);
                set("jing", 0, me);
                return 1;
        }
        me->receive_damage("jing", 180);
        if( query("qi", me)<300 )
        {
                message_vision(HIR "$N" HIR "长啸一声，双手搭上炉边，正待以内"
                               "力哺育炉火，突然眼前一黑...\n" NOR, me);
                tell_object(me, RED "你感到心虚气短。\n" NOR);
                set("qi", 0, me);
                return 1;
        }
        me->receive_damage("qi", 300);
        if( query("neili", me)<800 || query("max_neili", me)<1000 )
        {
                message_vision(HIR "$N" HIR "长啸一声，双手搭上炉边，正待以内"
                               "力哺育炉火，突然眼前一黑...\n" NOR, me);
                tell_object(me, RED "你感到内力枯竭。\n" NOR);
                set("neili", 0, me);
                return 1;
        }
        message_vision(HIR "$N" HIR "长啸一声，双手搭上炉边，刹那间，炉火沸腾，"
                       "一道" HIW "白光" HIR "，直冲霄汉。\n\n" NOR, me);

        ob = query_temp("item/making");
        
        lvl = me->query_skill("force");
        if( lvl > 2000 ) lvl = 2000;
        
        addn("item/point", query("item/point", ob) * lvl/500, ob);
        delete_temp("item/can_help", me);
        addn("max_neili", -200, me);
        addn("neili", -200, me);
        return 1;
}

protected int show_order()
{
        object me;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
        {
                message_vision("$N冷冷的坐在那里，理都不理$n。\n",
                               this_object(), me);
                return 1;
        }

        tell_rules(me);
        return 1;
}

void tell_rules(object me)
{
        tell_object(me, CYN @RULES
干将在你耳边悄声说道：
名字需要你来定，其它信息系统有缺省的描述，当然也可以由你自己为它自定描述。
当然了，最好不用让别人误会的词语字句噢。具体的方法如下。
    命名: name 中文名字 英文代号。   (必须有)
    描述: desc 武器的描述文字。      (可  选)
    装备: wieldmsg   装备时的描述。  (可  选)
    收起: unwieldmsg 收起时的描述。  (可  选)
描述时分行请用\n，除了英文代号以外所有的文字都可以用颜色，使用颜色的方法可以参照nick 。
如果你觉得可以了，就请告诉我(finish)，要是没看清楚，可以再问问我 < 规则 >

RULES NOR);
}

void waiting(object me, object ob, object moye)
{
        if( !objectp(me) )
                me = find_player(query("item/owner_id", ob));

        if( !objectp(me) )
        {
                message_vision("$N叹了口气说道：怎么这走了，算了算"
                               "了，去吧！\n", this_object());
                if( objectp(moye) )
                        delete_temp("item", moye);

                delete_temp("item");
                destruct(ob);
                return;
        }

        if( addn_temp("item/waited", -1) <= 0 )
        {
                // 等待超时
                if( objectp(moye) )
                        delete_temp("item", moye);

                log_file("static/item", sprintf("%s %s do timeout when make item of %s\n",
                                 log_time(), log_id(me),
                                 (ob ? filter_color(ob->name(1)) : "???")));
                if( objectp(ob) && present(ob, this_object()) )
                        destruct(ob);

                delete_temp("item", me);
                delete_temp("item");
                if( in_input(me) ) return;
                if( environment(me) == environment() )
                {
                        message_vision("$N皱了皱眉头说道：这人怎么这么"
                                       "磨蹭，算了，不要就不要吧！\n",
                                       this_object());
                        return;
                }
                message_vision("$N皱了皱眉头对$n说道：你这人怎么这么"
                               "磨蹭，不要就算了，恕不退款！\n",
                               this_object(), me);
                return;
        }

        if( environment(me) != environment() )
        {
                message_vision("$N疑惑地说道：人怎么跑掉了？算了，再等"
                               "他一会吧。\n", this_object());
        } else
        if( !in_input(me) )
        {
                message_vision(HIR "$N" HIR "催$n" HIR
                               "道：快点，快点，别磨蹭，否则我可就不做了。\n" NOR,
                               this_object(), me);
        }

        remove_call_out("waiting");
        call_out("waiting", 300, me, ob, moye);
}

protected void clear_data()
{
        object me;
        object ob;
        object moye;

        if (objectp(moye = present("mo ye")))
                delete_temp("item", moye);

        if (objectp(ob = query_temp("item/making")))
                destruct(ob);

        if (objectp(me = query_temp("item/player")))
                delete_temp("item", me);

        delete_temp("item");
        remove_call_out("waiting");
}

// 装备等级取消
int do_level(string arg)
{
        object me, ob;
        int level;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        if( !arg || sscanf(arg, "%d", level) != 1 )
        {
                write("格式不对！应该是：level 等级\n例如：level 30\n");
                return 1;
        }

        if( level<10 || level>query("level", me) )
        {
                write("装备的等级最低不能小于10级，最高也不能高于你现在的人物等级。\n");
                return 1;
        }

        if( level%10 != 0 )
        {
                write("装备的等级必须是10的倍数。\n");
                return 1;
        }

        ob = query_temp("item/making");
        set("item/level", level, ob);
        write(CYN "你决定打造" + level + "级的道具。\n" NOR);
        return 1;
}

int do_name(string arg)
{
        object me;
        object ob;
        string pname;
        string sname, sid;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        if( !arg || sscanf(arg, "%s %s", sname, sid) != 2 )
        {
                write("格式不对！应该是：命名 中文名字 英文名字\n例如：命名 长剑 sword\n");
                return 1;
        }

        // ILLEGAL_STR = "." 表示非法的输入
        if( (sname = converts(sname, 14, COLORABLE)) == ILLEGAL_STR )
                return 1;

        if( (sid = converts(sid, 8, NOCOLOR)) == ILLEGAL_STR )
                return 1;

        if( !sname || !sid )
        {
                message_vision("$N摇摇头，对$n道：不行不行，你好好个定个名字！\n",
                               this_object(), me);
                return 1;
        }

        if( file_size(ITEM_DIR+query("id", me)[0..0]+"/"+
                      query("id", me)+"-"+sid+".c") != -1 )
        {
                message_vision("$N摇摇头，对$n道：不好，你不要再用(" + sid +
                               ")这个英文代号了，换一个吧！\n",
                               this_object(), me);
                return 1;
        }

        if( !is_chinese(filter_color(sname)) )
        {
                command("kick "+query("id", me));
                command("say 不会写中文字怎么的？");
                return 1;
        }

        if( !is_legal_id(sid) )
        {
                command("say 英文代号必须全部用小写英文才可以！");
                return 1;
        }

        if( strlen(filter_color(sname)) < 4 )
        {
                command("say 我说你这名字起得也太短了吧，至少两个汉字！");
                return 1;
        }

        if( strlen(sid) < 3 )
        {
                command("say 我说你这代号起得也太短了吧，至少三个字符！");
                return 1;
        }

        if( sid == "qiankun" || sid == "belt" )
        {
                command("say 这代号是游戏里专用代号，请重新选择代号！");
                return 1;
        }

        if( sname[0] == 27 && sname[4] == 'm' )
        {
                // Add color prefix
                sname = NOR + sname;
        }

        ob = query_temp("item/making");
        set("item/name", sname, ob);
        set("item/id", sid, ob);

        write("名字：" CYN + sname + "    代号：" CYN + sid + NOR "\n");
        return 1;
}

int do_desc(string arg)
{
        object ob;
        object me;
        string chk;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        ob = query_temp("item/making");
        if( !query("item/name", ob) )
        {
                message_vision("$N瞪了$n一眼道：你还是先给它取好名字再考虑描述吧！\n",
                               this_object(), me);
                return 1;
        }

        if( !arg )
        {
                write("参照格式：应该是 desc 描述的文字。\n例如：一把"
                      "锋利的$n\\n它在阳光下闪闪发光 -- 其中\\n表示换行，$n代表道具。\n");
                return 1;
        }

        if( (arg = converts(arg, 200, COLORABLE)) == ILLEGAL_STR )
                return 1;

        arg = replace_string(arg, "$N", me->name(1));

        chk = filter_color(arg);
        if (strlen(chk) >= 2 && chk[0..1] == "你" || strsrch(chk, "\\n你") != -1)
                return notify_fail("对不起，描述不能以“你”字打头。\n");

        chk = replace_string(chk, " ", "");
        chk = replace_string(chk, "\\n", "");
        chk = replace_string(chk, "$n", "");
        if( !legal_chinese(chk) )
                return notify_fail("对不起，描述必须使用汉字和系统规定可以使用的代表符号。\n");

        arg=replace_string(arg,"$n",query("item/name", ob));
        arg = replace_string(arg, "\\n", "\n");
        arg = replace_string(arg, "\"", "");
        arg = replace_string(arg, "\\", "");
        arg = chinese_desc(arg);
        set("item/long", arg, ob);
        write(CYN "当你观察它的时候将会出现下列描述：\n" NOR + arg + "\n");
        return 1;
}

int do_wieldmsg(string arg)
{
        object ob;
        object me;
        string chk;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        ob = query_temp("item/making");
        if( !objectp(ob) ) return 0;
        if( !query("item/name", ob) )
        {
                message_vision("$N瞪了$n一眼道：你还是先给它取好名字再考虑描述吧！\n",
                               this_object(), me);
                return 1;
        }

        if( !arg )
        {
                write("参照格式：应该是 wieldmsg 描述的文字。\n例如："
                      "$N伸手一抖，抽出一把锋利长剑。 -- 其中$N表示你自"
                       "己，$n代表道具。\n");
                return 1;
        }

        if( (arg = converts(arg, 200, COLORABLE)) == ILLEGAL_STR )
                return 1;

        chk = filter_color(arg);
        if( strlen(chk) >= 2 && chk[0..1] == "你" || strsrch(chk, "\\n你") != -1 )
                return notify_fail("对不起，描述不能以“你”字打头。\n");

        chk = replace_string(chk, " ", "");
        chk = replace_string(chk, "\\n", "");
        chk = replace_string(chk, "$N", "");
        chk = replace_string(chk, "$n", "");
        if( !legal_chinese(chk) )
                return notify_fail("对不起，描述必须使用汉字和系统规定可以使用的代表符号。\n");

        // 这里不区分武器还是装备，在生成文件时自动选择一条信息
        arg = chinese_desc(arg);
        arg = replace_string(arg, me->name(1), "$N");
        set("item/wear_msg", arg, ob);
        set("item/wield_msg", arg, ob);
        arg = replace_string(arg, "\\n", "\n");
        arg = replace_string(arg, "$N", me->name(1));
        arg = replace_string(arg,"$n", query("item/name", ob));
        write(CYN "当你装备它的时候将会出现下列描述：\n" NOR + arg + "\n");
        return 1;
}

int do_unwield(string arg)
{
        object ob;
        object me;
        string chk;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        ob = query_temp("item/making");
        if( !query("item/name", ob) )
        {
                message_vision("$N瞪了$n一眼道：你还是先给它取好名字再考虑描述吧！\n",
                               this_object(), me);
                return 1;
        }

        if( !arg )
        {
                write("格式不对！应该是：unwield 描述的文字。\n例如："
                       "$N随手一挥，$n已入鞘内。 -- 其中$N表示你自己，$n代表道具。\n");
                return 1;
        }

        if( (arg = converts(arg, 200, COLORABLE)) == ILLEGAL_STR )
                return 1;

        chk = filter_color(arg);
        if( strlen(chk) >= 2 && chk[0..1] == "你" || strsrch(chk, "\\n你") != -1 )
                return notify_fail("对不起，描述不能以“你”字打头。\n");

        chk = replace_string(chk, " ", "");
        chk = replace_string(chk, "\\n", "");
        chk = replace_string(chk, "$N", "");
        chk = replace_string(chk, "$n", "");
        if( !legal_chinese(chk) )
                return notify_fail("对不起，描述必须使用汉字和系统规定可以使用的代表符号。\n");

        // 这里不区分武器还是装备，在生成文件时自动选择一条信息
        arg = chinese_desc(arg);
        arg = replace_string(arg, me->name(1), "$N");
        set("item/unwield_msg", arg, ob);
        set("item/remove_msg", arg, ob);
        arg = replace_string(arg, "\\n", "\n");
        arg = replace_string(arg,"$N", query("name", me));
        arg = replace_string(arg,"$n", query("item/name", ob));
        write(CYN "当你收回它的时候将会出现下列描述：\n" NOR + arg + "\n");
        return 1;
}

// 判断是否是合法的汉字
protected int legal_chinese(string str)
{
        int i;

        if( strlen(str) < 2 ) return 0;

        for( i = 0; i < strlen(str); i++ )
        {
                if( str[i] < 161 || str[i] == 255 ) return 0;
                if( (!(i % 2)) && str[i] >= 248 ) return 0;
        }

        return 1;
}

// 转换字符串中的颜色标志
protected string converts(string arg, int max_len, int no_color)
{
        int i;

        // 去除字符串中的空格，引号，避免被别人利用做破坏
        arg = replace_string(arg, " ", "");
        arg = replace_string(arg, "\"", "'");

        for( i = 0; i < strlen(arg) - 1; i++ )
        {
                if( arg[i] == '\\' && arg[i + 1] != 'n' )
                {
                        write("字符'\\'后面只能跟随n字符表示回车！\n");
                        return ILLEGAL_STR;
                }
        }

        arg = replace_string(arg, ",", "，");
        arg = replace_string(arg, ":", "：");
        arg = replace_string(arg, "?", "？");

        if( no_color )
        {
                arg = filter_color(arg, 1);
        } 
        else
        {
                arg = trans_color(arg, 3);
                if( strlen(arg) < strlen(NOR) ||
                    arg[strlen(arg) - strlen(NOR)..<1] != NOR )
                {
                        // append NOR at tail
                        arg += NOR;
                }
        }
        if( strlen(arg) > max_len + 30 ||
            strlen(filter_color(arg)) > max_len )
        {
                write("对不起，这个字符串太长了，请不要输入超过" + chinese_number(max_len) +
                      "个字符长的字符串。\n");
                // 表示非法的输入
                return ILLEGAL_STR;
        }
        return arg;
}

int do_finish()
{
        object me;
        object ob;
        object moye;
        string msg;
        int    level;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        if( !objectp(ob = query_temp("item/making")) )
        {
                // 数据不对，可能是由于BUG造成，也可能是因为干将被update过
                write("系统故障：数据不一致，你无法完成炼制道具！\n");
                delete_temp("item", me);
                delete_temp("item");
                if (objectp(moye = present("mo ye")))
                        delete_temp("item", moye);

                // 返回失败，停止进行
                return 0;
        }

        if( !query("item/name", ob) )
        {
                message_vision("$N瞪了$n一眼，说道：你怎么能不给它起个"
                               "名字？你要是不想要了就算了！\n",
                               this_object(), me);
                return 1;
        }

        if( !query("item/id", ob) )
        {
                message_vision("$N瞪了$n一眼，说道：你怎么能不给它起个"
                               "代号？你要是不想要了就算了！\n",
                               this_object(), me);
                return 1;
        }
        
        /*
        level = query("item/level", ob);
        if( !level )
        {
                level = (query("level", me)/10)*10;
                set("item/level", level, ob);
        }
        */
        
        // 显示 player 输入的信息
        msg = sprintf("干将对$N说：你的道具描述如下，请看看有没有错。\n");
        message_vision(msg, me);
        // 私有信息
        msg = sprintf("道具名字：%s   道具英文代号：%s\n\n",
                      query("item/name", ob),query("item/id", ob));

        //msg += sprintf("道具等级：%d\n\n",query("item/level", ob));

        if( query("item/long", ob) != "" )
                msg += sprintf(CYN"外观描述如下："NOR"\n%s\n\n",query("item/long", ob));
        else
                msg += "采用缺省的外观描述。\n";

        if( query("item/wield_msg", ob) != "" )
                msg += sprintf(CYN "装备时描述如下：" NOR "\n%s\n\n",
                               replace_string(query("item/wield_msg", ob),"\\n","\n"));
        else
                msg += "装备时采用缺省的描述。\n";

        if( query("item/unwield_msg", ob) != "" )
                msg += sprintf(CYN "收回时描述如下：" NOR "\n%s\n\n",
                               replace_string(query("item/unwield_msg", ob),"\\n","\n"));
        else
                msg += "收回时采用缺省的描述。\n";
                msg += CYN "如果没有问题，就可以继续进行了(y/n):" NOR;
                
        msg = replace_string(msg, "$N", query("name", me));
        msg = replace_string(msg, "$n", query("item/name", ob));

        tell_object(me, msg);

        // 判定 player 是否决定生成道具
        input_to("confirm_make", ob);
        return 1;
}

void confirm_make(string arg, object ob)
{
        mapping enchase, insert, require;
        mapping temp = ([]);
        object me;
        object moye;
        object item;
        string item_filename;

        me = this_player();

        if( !objectp(query_temp("item/making")) )
        {
                command("kick "+query("id", me));
                command("say 你太磨蹭了，这生意我不做了，恕不退货！");
                return;
        }

        if( arg != "y" && arg != "Y" )
        {
                message_vision("$N对道：那你还是再看看吧！\n", this_object());
                return;
        }

        message_vision("$N对$n说道：好，马上就好！\n",
                       this_object(), me);

        if( item_filename = create_file(ob) )
        {
                // clear the old item's data
                DBASE_D->set_object_data(ob, 0);
                destruct(ob);
                catch(call_other(item_filename, "???"));
                ob = find_object(item_filename);
                if( !ob )
                {
                        message_vision("$N一呆，对$n道：抱歉抱歉！出了一些问题！\n",
                                       this_object(), me);
                } else
                {
#ifdef DB_SAVE
                        if( !DATABASE_D->query_db_status() )
                                DATABASE_D->connect_to_database();
                        DATABASE_D->db_create_item(ob, ob->query_entire_dbase());
#endif
                        ob->move(me, 1);
                        ob->save();             // Create the record in dbase
                        message_vision("$N把"+query("name", ob)+"交给了$n。\n",
                                       this_object(), me);
                        
                        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/makeweapon");
                        log_file("static/item", sprintf("%s %s created  %s(%s)\n",
                                 log_time(), log_id(me),
                                 filter_color(ob->name(1)),query("id", ob)));
                }
        }
        if( objectp(moye = present("mo ye", environment())) )
                delete_temp("item", moye);

        delete_temp("item", me);
        delete_temp("item");
        remove_call_out("waiting");
}

// 生成道具文档, 需要一个的道具原料对象
// 生成以后建立 ITEM_DIR/???.c 然后删除旧的原料对象, 生成一件新的道具，返回文件名

// 关于原料对象各个属性的说明(item/)
// ------ 用户可以描述的属性
// name                 道具的名称， 必须要
// id                   道具的ID，   必须要
// long                 道具的描述，系统会在生成道具时自动添加关于炼制原料的描述
// wield_msg            装备武器的描述，如果没有系统会自动生成
// unwield_msg          收回武器时的描述
// wear_msg             穿上护甲时的描述
// unwear_msg           脱掉护甲时的描述

// ------ 不是用户描述的属性
// owner_id             制造者的ID
// owner_name           制造者的名字
// unit                 单位
// type                 道具的类型 weapon 或 armor
// stype                道具的子类别 weapon 为 sword, blade, whip, stick ； armor 为 armor
// ctype                道具的类别的中文名 weapon 为 剑、刀、鞭、杖 ； armor 为 护甲
// value                道具的价值
// point                伤害力

// ------ 说明是用户自练的道具的属性
// item_make            1

protected string create_file(object item_temp)
{
        string  buf;                    // 生成文件的缓冲区
        string  filename;
        string  desc;
        int     i;
        mapping info;
        string  ih;
        string  id;

        // 生成文件名
        id = query("item/owner_id", item_temp);
        filename = ITEM_DIR + id[0..0] + "/" + id +
                   "-"+query("item/id", item_temp)+".c";
        if( file_size(filename) != -1 )
        {
                write("无法生成档案，请通知巫师处理。\n");
                return 0;
        }
        assure_file(filename);
        buf = "// ITEM Made by player("+query("item/owner_name", item_temp)+
              ":"+query("item/owner_id", item_temp)+") "+filename+
              "\n// Written by GAN JIANG(Doing Lu 1998/11/2)\t" + ctime(time()) + "\n";
        info = query("item", item_temp);
        ih = up_case(info["stype"]);
        if( info["type"] == "weapon" )
        {
                // 生成武器道具文件
                desc = "这是由"+info["material_name"]+"炼制而成的一"+
                       info["unit"] + info["ctype"] + "。\n";

                desc += info["long"];
                if (desc[strlen(desc) - 1] != '\n')
                        desc += "\n";

                //info["makeinfo"] = info["ctype"] + "柄上刻着一行小字：" +
                //        info["owner_name"] + "(" + info["owner_id"] + ")\n";
                info["makeinfo"] = HIR "\n" + info["owner_name"] + "(" + info["owner_id"] + ")" + HIR " 出品\n" NOR;

                // 自动补充空信息
                if( info["wield_msg"] == "" )
                {
                        info["wield_msg"] = HIC "$N" HIC "一声清啸，" +
                                            (info["stype"] == "throwing" ? "握着一" : "抖出一") +
                                            info["unit"] + HIC "$n" HIC "。" NOR;
                }

                if( info["unwield_msg"] == "" )
                {
                        info["unwield_msg"] = "$N随手一抹，收起了$n。";
                }

                buf += "#include <ansi.h>\n";
                buf += "#include <weapon.h>\n\n";
                buf += "inherit " + ih + ";\n";
                buf += "inherit F_ITEMMAKE;\n\n";
                buf += "void create()\n{\n";
                buf += sprintf("\tset_name(\"%s\", ({ \"%s\" }));\n",
                                info["name"], info["id"]);
                buf += sprintf("\tset_weight(%d);\n",
                                item_temp->query_weight()*query("item/wscale", item_temp)/100);
                buf += sprintf("\tset(\"item_make\", 1);\n");
                buf += sprintf("\tset(\"unit\", \"%s\");\n", info["unit"]);
                buf += sprintf("\tset(\"long\", \"%s\");\n", desc);
                buf += sprintf("\tset(\"makeinfo\", \"%s\");\n", info["makeinfo"]);
                buf += sprintf("\tset(\"value\", %d);\n", info["value"]);
                if( info["stype"] == "throwing" )
                {
                       buf += sprintf("\tset(\"base_weight\", %d);\n",
                                       item_temp->query_weight()*query("item/wscale", item_temp)/10000);
                       buf += sprintf("\tset(\"base_unit\", \"枚\");\n");
                       // buf += sprintf("\tset(\"base_value\", %d);\n", info["value"] / 100);
                       buf += sprintf("\tset(\"base_value\", 1);\n");
                }
                buf += sprintf("\tset(\"point\", %d);\n", info["point"]);
                buf += sprintf("\tset(\"max_consistence\", %d);\n", 100);
                buf += sprintf("\tset(\"material\", \"%s\");\n", info["material_attrib"]);
                buf += sprintf("\tset(\"material_file\", \"%s\");\n", info["material_file"]);
                buf += sprintf("\tset(\"quality_level\", %d);\n", info["quality_level"]);
                if( info["stype"] == "throwing" )
                {
                        buf += sprintf("\tset(\"hand_msg\", \"%s\\n\");\n", info["wield_msg"]);
                        buf += sprintf("\tset(\"unhand_msg\", \"%s\\n\");\n", info["unwield_msg"]);
                } else
                {
                        buf += sprintf("\tset(\"wield_msg\", \"%s\\n\");\n", info["wield_msg"]);
                        buf += sprintf("\tset(\"unwield_msg\", \"%s\\n\");\n", info["unwield_msg"]);
                }
                buf += sprintf("\tif( !check_clone() ) return;\n\trestore();\n");
                if( info["stype"] == "throwing" )
                        buf += sprintf("\tset_amount(100);\n");   
                buf += sprintf("\tinit_%s(apply_damage());\n", info["stype"]);    
                buf += prop_segment(info["prop"], "");    

                if( info["prop2"] )
                        buf += prop_segment(info["prop2"], "weapon_prop/");
                        
                buf += sprintf("\n\tsetup();\n}\n\n");
                // 生成武器道具文件完毕
        }
        else
        {
                // 生成防护道具文件
                desc = "这是由"+info["material_name"]+"炼制而成的一"+
                       info["unit"] + info["ctype"] + "。\n";

                desc += info["long"];
                if (desc[strlen(desc) - 1] != '\n')
                        desc += "\n";

                //info["makeinfo"] = info["ctype"] + "柄上刻着一行小字：" +
                //        info["owner_name"] + "(" + info["owner_id"] + ")\n";
                info["makeinfo"] = HIR "\n" + info["owner_name"] + "(" + info["owner_id"] + ")" + HIR " 出品\n" NOR;

                // 自动补充空信息
                if (info["wear_msg"] == "")
                {
                        info["wear_msg"] = YEL "$N" YEL "装备" +
                                           YEL "$n" YEL "。" NOR;
                }
                if (info["remove_msg"] == "")
                {
                        info["remove_msg"] = YEL "$N" YEL "脱下了" +
                                             YEL "$n" YEL "。" NOR;
                }
                buf += "#include <ansi.h>\n";
                buf += "#include <armor.h>\n\n";
                buf += "inherit " + ih + ";\n";
                buf += "inherit F_ITEMMAKE;\n\n";
                buf += "void create()\n{\n";
                buf += sprintf("\tset_name(\"%s\", ({ \"%s\" }));\n",
                                info["name"], info["id"]);
                buf += sprintf("\tset_weight(%d);\n",
                                item_temp->query_weight()*query("item/wscale", item_temp)/100);
                buf += sprintf("\tset(\"item_make\", 1);\n");
                buf += sprintf("\tset(\"unit\", \"%s\");\n", info["unit"]);
                buf += sprintf("\tset(\"long\", \"%s\");\n", desc);
                buf += sprintf("\tset(\"makeinfo\", \"%s\");\n", info["makeinfo"]);
                buf += sprintf("\tset(\"value\", %d);\n", info["value"]);
                buf += sprintf("\tset(\"point\", %d);\n", info["point"]);
                buf += sprintf("\tset(\"max_consistence\", %d);\n", 100);
                buf += sprintf("\tset(\"material\", \"%s\");\n", info["material_attrib"]);
                buf += sprintf("\tset(\"material_file\", \"%s\");\n", info["material_file"]);
                buf += sprintf("\tset(\"quality_level\", %d);\n", info["quality_level"]);
                buf += sprintf("\tset(\"wear_msg\", \"%s\\n\");\n", info["wear_msg"]);
                buf += sprintf("\tset(\"remove_msg\", \"%s\\n\");\n", info["remove_msg"]);
                buf += sprintf("\tif( !check_clone() ) return;\n\trestore();\n");

                if( !info["prop"] )
		        buf += sprintf("\tset(\"armor_prop/armor\", apply_armor());\n");
                else
                        buf += prop_segment(info["prop"], "");
                
                if( info["prop2"] )
                        buf += prop_segment(info["prop2"], "armor_prop/");
                        
                buf += sprintf("\n\tsetup();\n}\n\n");
                // 生成防护道具文件完毕
        }
        buf += sprintf("string long() { return short() + query_makeinfo() + query(\"long\") + item_long(); }\n");

        if( save_item_file(filename, buf) == 1 )
                return filename;
        
        return 0;
}

// add mapping
/*
protected string prop_segment(mapping p, string path)
{
        string path2;
        string buf;
        string *ks;
        int i;

        buf = "";
        if (! p) return buf;

        ks = keys(p);
        for (i = 0; i < sizeof(ks); i++)
        {
                // check the paramter's type
                if (mapp(p[ks[i]]))
                {
                        path2 = path + ks[i] + "/";
                        buf += prop_segment(p[ks[i]], path2);
                } else
                {
                        if( intp(p[ks[i]]) )
                                buf += sprintf("\tset(\"%s\", %d);\n",
                                       path + (string)ks[i], p[ks[i]]);
                        else if( stringp(p[ks[i]]) )
                                buf += sprintf("\tset(\"%s\", \"%s\");\n",
                                       path + (string)ks[i], p[ks[i]]);
                }
        }

        return buf;
}
*/
protected string prop_segment(mapping p, string path)
{
        string buf;
        string *ks;
        int i;

        buf = "";
        if (! p) return buf;

        ks = keys(p);
        for (i = 0; i < sizeof(ks); i++)
        {
                // check the paramter's type
                if (mapp(p[ks[i]]))
                {
                        path += ks[i] + "/";
                        buf += prop_segment(p[ks[i]], path);
                } else
                        buf += sprintf("\tset(\"%s\", %s);\n",
                                       path + ks[i], to_string(p[ks[i]]));
        }

        return buf;
}
// filename 是写入文档的名称，已经包含有路径
// content 是写入文档的内容
protected int save_item_file(string filename, string content)
{
        rm(filename);
        if( write_file(filename, content) )
        {
                VERSION_D->append_sn(filename);
                return 1;
        } else
        {
                write("写入档案(" + filename + ")时出错，请通知巫师处理。\n");
                return 0;
        }
}

int do_discard(string arg)
{
        mapping rare;
        string desc, file;
        string type;
        object money;
        object ob, item;
        object me;
        int n;

        if (! arg)
                return notify_fail("你去退回什么东西？\n");

        me = this_player();
        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上没有这种东西。\n");

        message_vision("$n拿出一"+query("unit", ob)+ob->name()+
                       "对$N说：“这个东西我想退掉了...”\n",
                       this_object(), me);

        if( !ob->is_item_make() )
        {
                command("heng");
                command("say 这不是我这里出来的东西，我可不能负责。");
                return 1;
        }

        if( query("equipped", ob) ) 
                return notify_fail("你先解除" + ob->name() + "的装备再说！\n"); 

        if( !wizardp(me) && ob->item_owner() != query("id", me) )
        {
                command("kick "+query("id", me));
                command("say 你拿了别人的东西还敢来我这里？以为我是傻子？");
                return 1;
        }

        command("sigh");
        command("say 一千多年来还没有什么人嫌我的货色不好的，算了！算了！");
        message_vision("$N接过$n递过来的" + ob->name() + "，随手"
                       "扔进了火炉，呆呆的望了半晌。\n",
                       this_object(), me);


        item = new(query("material_file", ob));
        item->move(me, 1);
        if( ob->is_weapon() )
        {
                rare = query("weapon_prop", ob);
                type = query("skill_type", ob);
        }
        else
        {
                rare = query("armor_prop", ob);
                type = query("armor_type", ob);
        }
        map_delete(rare, "damage");
        map_delete(rare, "unarmed_damage");
        map_delete(rare, "armor");
        if( sizeof(rare) )
        {
                item = new("/clone/tessera/jhunshi");
                set("quality_level", query("quality_level", ob), item);
                set("enchase/type", type, item);
                set("enchase/apply_prop", rare, item);
        }
        else
                item = new("/clone/goods/jhunshi");
        item->move(me, 1);

        message_vision("不一会儿" + ob->name() + "就熔化成一堆材料。\n",
                       this_object(), me);

        command("say 这是打造材料，退回给你！");
        message_vision("$N拿出一"+query("unit", item)+item->name()+"和一块精魂石交给"
                       "$n。\n", this_object(), me);
                       
        command("say 你既然不满意我的东西，我也不能收你的钱，"
                "这些算是我退回给你的！");
        n = (query("value", ob)*8/10+9999)/10000;
        if( !n )
        {
                money = new("/clone/money/silver");
                money->set_amount(1);
        } else
        {
                money = new("/clone/money/gold");
                money->set_amount(n);
        }

        message_vision("$N拿出一些" + money->name() + "交给"
                       "$n。\n", this_object(), me);
        log_file("static/item", sprintf("%s %s discard  %s(%s)\n",
                                log_time(), log_id(me),
                                filter_color(ob->name(1)),query("id", ob)));
        delete("can_summon/"+query("id", ob), me);
        file = base_name(ob) + ".c";
        DBASE_D->clear_object(ob);
        if( sscanf(file, "/data/item/%*s") )
                rm(file);
        money->move(me, 1);
        return 1;
}

int do_notch(string arg)
{
        object me, ob, ob1;
        string *runes;
        int i, n;

        if( !arg )
                return notify_fail("你要将什么东西开槽？\n");

        me = this_player();
        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上没有这种东西。\n");

        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的装备再说！\n");

        if( query("balance", me)<10000000 )
                return notify_fail("你在钱庄里的存款不够支付道具开槽费用。\n");

        message_vision(CYN"$n拿出一"+query("unit", ob)+ob->name()+
                       CYN "对$N说：我想请您给" + ob->name() + CYN "开些镶嵌用的凹槽。\n",
                       this_object(), me);

        if( !ob->is_item_make() )
        {
                command("heng");
                command("say 我且能给这如此平凡之物开槽钻孔？！");
                return 1;
        }

        if( !query("armor_type", ob) && !query("skill_type", ob) )
        {
                command("say 我只给兵器或防具类型的道具开槽钻孔。");
                return 1;
        }
        
        if( !query("magic/imbue_ok", ob) )
        {
                command("say 只有准10LV的装备才可以开槽钻孔。");
                return 1;
        }
        /*
        if( !query("rare/apply_prop", ob) )
        {
                command("say 你还是先将"+ob->name()+"融合稀有度高的精魂石碎片后再来开槽钻孔。");
                return 1;
        }
        */
        
        n = query("enchase/flute", ob);
        n++;
        
        if( n > 7 )
                return notify_fail(ob->name() + "已经再开槽到极限了！\n");
                        
        if( !query("armor_type", ob) || (query("armor_type", ob) != "rings" && 
             query("armor_type", ob) != "neck" && query("armor_type", ob) != "charm") )
        {
                if( !ob->is_weapon() && !ob->is_unarmed_weapon() && n > 5 )
                        return notify_fail(ob->name() + "已经再开槽到极限了！\n");
                runes = equip_sockets[to_string(n)];
        }
        else
        {
                if( n > 3 )
                        return notify_fail(ob->name() + "已经再开槽到极限了！\n");
                        
                runes = rings_sockets[to_string(n)];
        }
        
        for( i=0; i< sizeof(runes); i++ )
        {  
                // 需要材料
                if( !objectp(present(runes[i], me)) )
                        return notify_fail("你好象还没备齐开槽符文"+runes[i]+"吧？\n");
        }

        for( i=0; i< sizeof(runes); i++ )
        {  
                if( objectp(ob1 = present(runes[i], me)) )
                        destruct(ob1);
        }

        message_vision(HIM "$N接过$n" HIM "手中的" + ob->name() + HIM "及符文......\n" NOR,
                     this_object(), me);

        addn("enchase/flute", 1, ob);
        
        switch(query("material", ob))
        {
        case "tian jing":
                set("enchase/SN", 8, ob);
                break;
        case "no name"  :
                set("enchase/SN", 16, ob);
                break;
        default         :
                break;
        }
        /*
        switch(query("quality_level", ob) )
        {
        case 2 :
                set("enchase/SN", 4, ob);
                break; 
        case 3 :
                set("enchase/SN", 8, ob);
                break;
        case 4 :
                set("enchase/SN", 12, ob);
                break;
        case 5 :
                set("enchase/SN", 16, ob);
                break;
        case 6 :
                set("enchase/SN", 25, ob);
                break;                            
        default         :
                break;
        }
        */

        ob->save();

        addn("balance", -10000000, me);
        me->save();

        message_vision(HIW "只见一束眩光闪过，" + ob->name() + HIW"上面豁然多了一个圆形的小孔。\n\n" NOR, this_object(), me);

        message_vision(HIC "$N把" + ob->name() + HIC "交还给了$n。\n" NOR, this_object(), me);
        command("say 行了，行了！你可以走了。");
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/notch");
        return 1;
}

int check_legal_name(string name, int max_len)
{
        int i;

        i = strlen(name);
        if( (strlen(name) < 2) || (strlen(name) > max_len ) )
        {
                write(sprintf("对不起，中文字必须是 1 到 %d 个中文字。\n",
                      max_len / 2));
                return 0;
        }

        if( max_len < 9 && ! is_chinese(name) )
        {
                write("对不起，请您用「中文」为套装取名字。\n");
                return 0;
        }
        return 1;
}

void get_modname(string arg, object me, object ob)
{
        mapping prop;
        string arg_old;
        string type;
        object ob_reset;

        if( arg == "q" || arg == "Q" ) {
                write("你取消了绿化套装，将装备取回。\n");
                return;
        }
        if( query_temp("big5", me) )
                arg = LANGUAGE_D->Big52GB(arg);

        arg_old = arg;
        arg = trans_color(arg, 3);
        arg = filter_color(arg, 1);

        if (! check_legal_name(arg, 8))
        {
                write("请给你的绿化装备起个套装名称(不要超过4个字，可加颜色)：\n");
                input_to( (: get_modname :), me, ob);
                return;
        }
        
        if( !(type = query("skill_type", ob)) )
                type = query("armor_type", ob);
                
        arg = arg_old;
        arg = trans_color(arg, 3);
        //arg = HIG "※" NOR+arg+NOR+HIG "※" NOR;

        prop = EQUIPMENT_D->apply_ultimate_prop(ob, type, 5);
        set("enchase/mod_prop", prop, ob);
        set("mod_name", arg, ob);
        set("mod_mark", base_name(ob), ob);
        if( !query("mod_level", ob) )
                set("mod_level", "1", ob);
        
        if( objectp(ob_reset = present("ability2 crystal", me)) && query("upsuit_level", ob_reset) >= to_int(query("mod_level", ob)) )
        {
                set("mod_level", to_string(query("upsuit_level", ob_reset)), ob);
                delete("upsuit_level", ob_reset);
        }
        ob->save();
        delete_temp("paid/dosuit", me);

        message_sort(HIY "\n干将小心翼翼地接过" + ob->name() + HIY "，轻轻地来回抚摩，但见" + ob->name() +
                     HIY "表面微微泛起紫色光芒，若隐若现，犹如遥远夜空中的一点星光。随即，干将将" + ob->name() +
                     HIY "交予旁边的莫邪，莫邪微微一笑，双手托起" + ob->name() + HIY "，口中默默地念着奇怪的咒语 ……" +
                         "一柱香后" + ob->name() + HIY "表面的紫芒消失不见，但旋即被数道青芒包裹着，并伴随着" +
                         "一道金色的电光，异常闪耀，似乎要将一切吞噬……莫邪轻嘘一声，又小心翼翼地将" + ob->name() + HIY "交还到" +
                         "干将手中，干将再次轻抚" + ob->name() + HIY "，奇怪的是，" + ob->name() + HIY "周围的光芒" +
                         "突然间消失，回复了平静！\n\n" NOR, me);

        CHANNEL_D->do_channel(this_object(), "chat", HIY "恭喜" + query("name", me) + HIY "的" + ob->name() + HIY "升级为" + 
                                                          suit_level[query("mod_level", ob)] + HIY "品质！\n" NOR);
                                                          
        tell_object(me, HIG "干将把 " + ob->name() + HIG + "交给了你。\n" NOR);
        MYGIFT_D->check_mygift(me, "newbie_mygift/dosuit");
        return;
}

int do_suit(string arg)
{
        object me, obj;

        string *type_list = ({
                "head",
                "waist",
                "boots",
                "surcoat",
                "armor",
                "cloth",
                "wrists",
                "neck",
                "rings",
                "charm",
        });

        me = this_player();

        if( !query_temp("paid/dosuit", me) ) 
                return notify_fail("干将说道：”你想干什么，别打搅我思考！“\n");

        if( !arg ) return notify_fail("你要为什么物品绿化套装属性 dosuit <物品ID> \n");

        if( !objectp(obj = present(arg, me)) )
                return notify_fail("你身上没有这样道具。\n");
        
        if( query("equipped", obj) )
                return notify_fail("你先解除" + obj->name() + "的装备再说！\n");
                
        if( !obj->is_item_make() )
                return notify_fail("这样物品不能升级套装属性。\n");
        
        /*
        if (obj->item_owner() != query("id", me))
                return notify_fail("这个，好象不属于你吧，这样不大合适。\n");
        */
        
        // 判断目标是否属于可以升级的套装部件
        if( !obj->is_weapon() && !obj->is_unarmed_weapon() )
                if (member_array(query("armor_type", obj), type_list) == -1)
                        return notify_fail("该装备种类不能进行绿化套装，详情见 help suit 说明。\n");

        if( !obj->is_ultimate() )
                return notify_fail(obj->name() + NOR "的品质还不完美，无法绿化套装！\n");

        if( query("balance", me) < 100000000 )
                return notify_fail("你银行里的钱不够吧，为" + obj->name() + NOR "绿化套装需要" +
                                   HIY "一万两黄金，" NOR "还是凑够再来吧！\n");

        // 判断目标部件是否已经绿化套装
        if( query("mod_name", obj) )
        {
                if( !query_temp("pending/dosuit", me) )
                {
                        set_temp("pending/dosuit", 1, me);
                        return notify_fail(obj->name() + NOR "已经被绿化成套装的一个部件了，想要重新绿化请再输入一次dosuit！\n");
                }

                //delete("mod_level", obj);
                delete("mod_name", obj);
                delete("enchase/mod_prop", obj);
        }

        delete_temp("pending/dosuit", me);
        addn("balance", -100000000, me);

        write("请给你的绿化套装起个套装名称(不要超过4个字，可加颜色)：\n");
        input_to( (: get_modname :), me, obj);
        return 1;
}

int do_upsuit(string arg)
{
        object me, ob, item;
        object ob_reset;
        mixed level;

        me = this_player();
        
        if( !arg ) return notify_fail("你要提升哪个套装部件品级 upsuit <物品ID> \n");

        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上没有这样道具。\n");
        
        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的装备再说！\n");
                
        if( !ob->is_item_make() )
                return notify_fail("这样物品不能升级套装品级。\n");
        
        if( !query("mod_name", ob) )
                return notify_fail("你先绿化套装后，才能升级套装品级。\n");
        
        if( (level = query("mod_level", ob)) == "4" )
                return notify_fail(ob->name() + NOR "已达到最高级别—造化神器！\n");
        
        /*       
        if( ob->item_owner() != query("id", me) )
                return notify_fail("这个，好象不属于你吧，这样不大合适。\n");
        */
        
        if( !objectp(ob_reset = present("ability2 crystal", me)) || query("upsuit_level", ob_reset) <= to_int(level) )
        {
                if( !objectp(item = present("hongmeng lingqi", me)) )
                        return notify_fail("你好象还没备齐鸿蒙灵气吧？\n");
        }
        
        if (query("balance", me) < 100000000)
                return notify_fail("你银行里的钱不够吧，为" + ob->name() + NOR "提升套装品级需要" +
                                   HIY "一万两黄金，" NOR "还是凑够再来吧！\n");
        
        level = to_int(level);
        level++;
        if( objectp(ob_reset) && query("upsuit_level", ob_reset) == level )
                delete("upsuit_level", ob_reset);
                
        level = to_string(level);
        set("mod_level", level, ob);
        ob->save();
        message_sort(HIY "\n干将小心翼翼地接过" + ob->name() + HIY "，轻轻地来回抚摩，但见" + ob->name() + 
                     HIY "表面微微泛起紫色光芒，若隐若现，犹如遥远夜空中的一点星光。随即，干将将" + ob->name() + 
                     HIY "交予旁边的莫邪，莫邪微微一笑，双手托起" + ob->name() + HIY "，口中默默地念着奇怪的咒语 ……" + 
                         "一柱香后" + ob->name() + HIY "表面的紫芒消失不见，但旋即被数道青芒包裹着，并伴随着" + 
                         "一道金色的电光，异常闪耀，将"+(objectp(item) ? item->name():"超能力水晶")+HIY"吞噬……莫邪轻嘘一声，又小心翼翼地将" + ob->name() + HIY "交还到" + 
                         "干将手中，干将再次轻抚" + ob->name() + HIY "，奇怪的是，" + ob->name() + HIY "周围的光芒" + 
                         "突然间消失，回复了平静！\n\n" NOR, me);
        
        if( objectp(item) ) destruct(item);
        addn("balance", -100000000, me);

        CHANNEL_D->do_channel(this_object(), "chat", HIY "恭喜" + query("name", me) + HIY "的" + ob->name() + HIY "升级为" + 
                                                          suit_level[query("mod_level", ob)] + HIY "品质！\n" NOR);

        if( query("mod_level", ob) == "4" )                                           
                CHANNEL_D->do_channel(get_object(__DIR__"moye"), "chat", HIC "不想千年之后，能再次见到传说中的造化神器，实在是死而无憾也！\n" NOR);                                                    

        tell_object(me, HIG "干将把 " + ob->name() + HIG + "交给了你。恭喜你" + 
                       ob->name() + HIG "升级为" + suit_level[query("mod_level", ob)] + HIG "品质！\n" NOR);
        return 1;
}

/*
int do_show(string arg)
{
        mapping props;
        string str, what, element;
        string *apply;
        object me, ob;
        int i, n, level;
       
        if( !arg )
                return notify_fail("你要亮出什么东西？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上没有这种东西。\n");

        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的装备再说！\n");
                
        message_vision("$n拿出一"+query("unit", ob)+ob->name()+
                       "对$N说：“拜托拜托...”\n",
                       this_object(), me);

        if( !ob->is_item_make() )
        {
                command("heng");
                command("say 这...这...我看还是算了吧！");
                return 1;
        }
        
        if( !mapp(props = query("enchase/apply_prop", ob)) || !mapp(query("insert", ob)) )
                return notify_fail(ob->name() + NOR "连宝石都没有镶嵌，如何能强化。\n");
        
        level = query("qianghua/level", ob);
        what = qianghua_rune[to_string(level)];
        
        str = CYN"干将说道：强化"+ob->name()+CYN"到"+(level+1)+"星需要材料有：乾坤圣水、";
        str += "符文"+what + " 3个以及下列的属性元素\n";
          
        props = query("enchase/apply_prop", ob);
        apply = keys(props);
        n = sizeof(apply);
        for( i=0;i<n;i++ )
        {
                element = apply[i];
                str += EQUIPMENT_D->chinese(element)+"元素1个"; 
                if( i+1 == n ) str += "，\n";
                else if( (i+1) % 6 == 0 ) str += "、\n"; 
                else str += "、";      
        }
        
        str += "如果你备齐了以上材料，请输入qianghua <装备>进行强化。\n" NOR;
        tell_object(me, str);

        return 1;
}
*/

int do_restore(string arg)
{
        string file;
        object me, ob, ob_reset;
        int level;
       
        if( !arg )
                return notify_fail("你要亮出什么东西？\n");

        me = this_player();
        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上没有这种东西。\n");

        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的装备再说！\n");
                
        message_vision("$n拿出一"+query("unit", ob)+ob->name()+
                       "对$N说：“拜托拜托...”\n",
                       this_object(), me);

        if( !ob->is_item_make() || !query("qianghua/level", ob) )
        {
                command("heng");
                command("say 这...这...我看还是算了吧！");
                return 1;
        }

        if( ob->item_owner() != query("id", me) )
        {
                command("heng");
                command("say 这是你的东西吗？没收了！");
                destruct(ob);
                return 1;
        }
        
        message_vision("$N接过$n递过来的" + ob->name() + "，随手"
                       "扔进了火炉，呆呆的望了半晌。\n",
                       this_object(), me);
                       
        ob_reset = new("/clone/goods/ability2_crystal");
         
        message_vision("不一会儿" + ob->name() + "就熔化形成一个" + ob_reset->name() + "。\n",
                       this_object(), me);
                       
        level = query("qianghua/level", ob); // 强化星级
        if( level ) set("qianghua_level", level, ob_reset);
        level = to_int(query("mod_level", ob)); // 套装等级
        if( level ) set("upsuit_level", level, ob_reset);
        
        set("set_data", 1, ob_reset);
        ob_reset->move(me, 1);

        message_vision("$N把" + ob_reset->name() + "交给"
                       "$n。\n", this_object(), me);
        log_file("static/ob_reset", sprintf("%s %s reset %s(%s)\n",
                                log_time(), log_id(me),
                                filter_color(ob->name(1)),query("id", ob)));
        delete("can_summon/"+query("id", ob), me);
        file = base_name(ob) + ".c";
        DBASE_D->clear_object(ob);
        rm(file);

        return 1;
}

int do_increase(string arg)
{
        mapping props;
        string what, item, element;
        object me, ob, crystal;
        object ob_reset;
        object ob_water, ob_zz1, ob_zz2, ob_zz3;
        object ob_rune1, ob_rune2, ob_rune3;
        object *obs;
        int level, success;
        mixed value;
        string *apply;
        int i, n;
        int wash;
        int rate, rate2;
        int vip_level;

        me = this_player();
        
        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg )
                return notify_fail("强化装备指令格式：qianghua <装备> 或 qianghua <装备> with <强化水晶>\n");
        
        if( sscanf(arg, "%s with %s", arg, item ) == 2 )
        {
                if( !objectp(ob = present(arg, me)) )
                        return notify_fail("你身上没有这样装备用来强化。\n");
                
                if( !objectp(crystal = present(item, me)) )
                        return notify_fail("你身上没有这样道具用来辅助强化。\n");

                if( query("id", crystal) != "qianghua crystal" )
                        return notify_fail("你身上没有强化水晶来辅助强化。\n");
        } 
        else     
        {
                if( !objectp(ob = present(arg, me)) )
                        return notify_fail("你身上没有这样装备用来强化。\n");
        }
        
        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的装备再说！\n");
                
        if( !ob->is_item_make() )
                return notify_fail("这样物品不能强化属性。\n");
        
        /*
        if( ob->item_owner() != query("id", me) )
                return notify_fail("这个，好象不属于你吧，这样不大合适。\n");
        */
        
        if( !mapp(props = query("enchase/apply_prop", ob)) || !query("insert", ob) )
                return notify_fail(ob->name() + NOR "必须镶嵌宝石后才能强化。\n");
                
        if( !query("ultimate/69", ob) && !query("ultimate/87", ob) && !query("ultimate/105", ob) )
               return notify_fail(ob->name() + NOR "没有达到上古或更高等级，无法强化！\n");
        
        level = query("qianghua/level", ob); 
        if( level >= 9 ) return notify_fail(ob->name() + NOR "已经强化到最高等级了！\n");
        if( !objectp(ob_reset = present("ability2 crystal", me)) || query("qianghua_level", ob_reset) <= level ) // 超能力水晶
        {    
                // 需要乾坤圣水
                if( !objectp(ob_water = present("bless water", me)) )
                        return notify_fail("你好象还没备齐乾坤圣水吧？\n");    
              
                // 需要符文
                what = qianghua_rune[to_string(level)];  
                if( !objectp(ob_rune1 = present(what + " 1", me)) || !ob_rune1->is_rune() )
                        return notify_fail("你好象还没备齐3个"+what+"吧？\n");

                if( !objectp(ob_rune2 = present(what + " 2", me)) || !ob_rune2->is_rune() )
                        return notify_fail("你好象还没备齐3个"+what+"吧？\n");

                if( !objectp(ob_rune3 = present(what + " 3", me)) || !ob_rune3->is_rune() )
                        return notify_fail("你好象还没备齐3个"+what+"吧？\n");
        }
        // 需要黄金一万两
        if( query("balance", me) < 100000000 )
                return notify_fail("你的银行里好象没有备齐1万两黄金吧。\n");
         
        apply = keys(props);
        n = sizeof(apply);
        for( i=0;i<n;i++ )
        {
                break; // 取消强化需要的元素，简单化
                
                if( objectp(ob_reset) && query("qianghua_level", ob_reset) > level ) break;
                // 需要强化材料
                element = apply[i];
                if( !objectp(ob_zz1 = present(element + " 1", me)) )
                        return notify_fail("你好象还没备齐强化需要的3个"+element+"元素吧？\n");

                if( base_name(ob_zz1) != "/inherit/template/element/element" )
                        return notify_fail("你好象还没备齐强化需要的3个"+element+"元素吧？\n");

                if( !objectp(ob_zz2 = present(element + " 2", me)) )
                        return notify_fail("你好象还没备齐强化需要的3个"+element+"元素吧？\n");

                if( base_name(ob_zz2) != "/inherit/template/element/element" )
                        return notify_fail("你好象还没备齐强化需要的3个"+element+"元素吧？\n");

                if( !objectp(ob_zz3 = present(element + " 3", me)) )
                        return notify_fail("你好象还没备齐强化需要的3个"+element+"元素吧？\n");

                if( base_name(ob_zz3) != "/inherit/template/element/element" )
                        return notify_fail("你好象还没备齐强化需要的3个"+element+"元素吧？\n");
        }
        for( i=0;i<n;i++ )
        {
                break; // 取消强化需要的元素，简单化
                if( objectp(ob_reset) && query("qianghua_level", ob_reset) > level ) break;
                element = apply[i];
                if( !objectp(ob_zz1 = present(element + " 1", me)) )
                        return notify_fail("你好象还没备齐强化需要的3个"+element+"元素吧？\n");
                if( !objectp(ob_zz2 = present(element + " 2", me)) )
                        return notify_fail("你好象还没备齐强化需要的3个"+element+"元素吧？\n");
                if( !objectp(ob_zz3 = present(element + " 3", me)) )
                        return notify_fail("你好象还没备齐强化需要的3个"+element+"元素吧？\n");
                
                destruct(ob_zz1);
                destruct(ob_zz2);
                destruct(ob_zz3);
        }        
        
        if( !objectp(ob_reset) || query("qianghua_level", ob_reset) <= level )
        {
                destruct(ob_water);
                destruct(ob_rune1);
                destruct(ob_rune2);
                destruct(ob_rune3);
        }
        addn("balance", -100000000, me);
               
        command("say 不错，既然我要的东西你都备齐了，我这就开始强化"+ob->name()+NOR+CYN"。\n"NOR);
        
        vip_level = me->query_viplevel();
        
        if( level == 0 ) success = 70;
        else if( level == 1 ) success = 70;
        else if( level == 2 ) success = 70;
        else if( level == 3 ) success = 50;
        else if( level == 4 ) success = 35;
        else if( level == 5 ) success = 20;
        else if( level == 6 ) { if( vip_level == 7 ) success = 22; else success = 15; }
        else if( level == 7 ) { if( vip_level == 7 ) success = 14; else success = 10; }
        else if( level == 8 ) { if( vip_level == 7 ) success = 7; else success = 5; }
        
        if( query("material", ob) == "no name" )
                success += 5;

        message_vision(HIW "\n$N将乾坤圣水、符文和元素粉末混合在一起融合，然后将融合后的乾坤圣水缓缓洒在" + ob->name() + HIW "上，\n顷刻间"
                       + ob->name() + HIW "犹如烈火中重生一般，散发出绚目的光彩！\n\n", this_object(), me);
        
        rate = random(100);
        /*
        rate2 = random(100);
        rate = (rate + rate2)/2;
        */
        if( rate < success || (level < 6 && objectp(crystal)) || query("id", me) == "lonely" || (objectp(ob_reset) && query("qianghua_level", ob_reset) > level) )
        {      
                level++;
                if( objectp(ob_reset) && query("qianghua_level", ob_reset) == level )
                        delete("qianghua_level", ob_reset); // 消除超能力水晶上强化星级的记录
                if( objectp(ob_reset) && query("qianghua_level", ob_reset) >= level ) // 只能使用一次效果 by lonely
                {
                        log_file("static/qianghua", sprintf("%s %s have qianghua %s to LV %d.\n",TIME_D->replace_ctime(time()),query("id", me),base_name(ob),level));
                }
                        
                for(  i=0;i<n;i++ )
                {               
                        what = apply[i];
                        value = EQUIPMENT_D->query_prop_value(what, level, 1); // 强化值
                        // set("enchase/pink_prop/"+what, value, ob); 
                        set("qianghua/apply_prop/"+what, value, ob); 
                }
                addn("qianghua/level", 1, ob);
                ob->save();
                tell_object(me, HIG "强化成功！" + ob->name() + HIG "强化等升至 " + 
                                sprintf(HIY "%d" HIG, query("qianghua/level", ob)) + " 星。\n" NOR); 
                if( query("qianghua/level", ob) >= 4 ) 
                { 
                        if( !wizardp(me) )
                        CHANNEL_D->channel_broadcast("news",  
                                                      YEL "听说" + ob->name() +  
                                                      YEL "强化至 " HIR + sprintf("%d", query("qianghua/level", ob)) +  
                                                      YEL " 星。\n" NOR); 
                } 
                if( query("qianghua/level", ob) >= 9 )
                {
                        if( !wizardp(me) )
                        CHANNEL_D->channel_broadcast("news",
                                                      YEL "恭喜" + ob->name() +  
                                                      YEL "强化为旷世神兵！\n" NOR); 
                }
                tell_object(me, HIC "你感受" + ob->name() + HIC "发生了不可言喻的变化。\n" NOR); 
                if( objectp(crystal) )
                        destruct(crystal);
                        
                MYGIFT_D->check_mygift(me, "newbie_mygift/qianghua");     
        }        
        else
        {
                if( query("qianghua/level", ob) > 4 )
                {
                        if( objectp(crystal=present("shengling crystal", me)) )
                        {
                                destruct(crystal);
                                tell_object(me, HIR "很遗憾，强化失败。\n" NOR);
                        }
                        else
                        {
                                set("qianghua/level", 4, ob);
                                ob->save();
                                tell_object(me, HIR "很遗憾，强化失败了(强化等级降为4级）！\n" NOR); 
                        }
                }
                else
                        tell_object(me, HIR "很遗憾，强化失败。\n" NOR);
        }
        message_vision("$N" NOR "拿出" + ob->name() + NOR "还给$n" NOR "。\n" NOR, this_object(), me);
        return 1;
}
