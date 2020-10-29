#include <ansi.h>
#include "lingxiao.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();
string ask_book();
string ask_skill();

void create()
{
        set_name("史婆婆", ({"shi popo", "shi", "popo"}));
        set("long", "她是雪山派掌门人白自在的妻子，虽说现在人已显\n"
                    "得苍老，十年前提起“江湖一枝花”史小翠来，武\n"
                    "林中却是无人不知。\n");
        set("title", "金乌派开山祖师");
        set("gender", "女性");
        set("age", 58);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 4200);
        set("max_jing", 3500);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 200);
        set("combat_exp", 2000000);

        set("inquiry",([
                "金乌刀谱":(:ask_book:),
                "金乌坠地":(:ask_skill:),
  "赤焰暴长" : (: ask_skill1 :),
        ]));

        set_skill("force", 220);
        set_skill("xueshan-neigong", 220);
        set_skill("wuwang-shengong", 180);
        set_skill("dodge", 220);
        set_skill("taxue-wuhen", 220);
        set_skill("cuff", 220);
        set_skill("lingxiao-quan", 220);
        set_skill("strike", 220);
        set_skill("piaoxu-zhang", 220);
        set_skill("sword", 200);
        set_skill("hanmei-jian", 200);
        set_skill("yunhe-jian", 200);
        set_skill("xueshan-jian", 200);
        set_skill("blade", 240);
    set_skill("jinwu-blade", 240);
        set_skill("parry", 200);
        set_skill("literate", 200);
        set_skill("martial-cognize", 180);

        map_skill("force", "wuwang-shengong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("cuff", "lingxiao-quan");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "xueshan-jian");
      map_skill("blade", "jinwu-blade");
  map_skill("parry", "jinwu-blade");

        prepare_skill("strike", "piaoxu-zhang");
        prepare_skill("cuff", "lingxiao-quan");

        create_family("凌霄城", 5, "掌门夫人");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
     (: perform_action, "blade.jinwu" :),
                (: perform_action, "cuff.jue" :),
                (: perform_action, "strike.piao" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("count", 1);
        setup();

        carry_object("/clone/weapon/chaidao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("family/master_name", me) == "白自在" || 
           query("family/master_name", me) == "白万剑" )
        {
                command("say 嘿，你既然拜了老鬼小鬼为师，还来找我这老婆子作甚？");
                return;
        }

        if( query("shen", me)<10000 )
        {
                command("say 我武功不传不义之人，你走开。");
                return;
        }

        if( query("combat_exp", me)<200000 )
        {
                command("say 你现在江湖经验太浅，还是多锻炼锻炼再来吧。");
                return;
        }

        if ((int)me->query_skill("xueshan-neigong", 1) < 100)
        {
                command("say 你本门的内功心法太差，修炼好了之后再来找我。");
                return;
        }

        command("haha");
        command("say 今日我就收下你，你须得勤练功，他日必能胜过那个老鬼。");
        command("recruit "+query("id", me));
}
mixed ask_skill1()
{
        object me;

        me = this_player();
  if( query("can_perform/jinwu-blade/chi", me) )
                return "这招我不是已经教过你了吗？自己下去多练吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪里来的？给我滚开！";

 if (me->query_skill("jinwu-blade", 1) < 1)
                return "你连金乌刀法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<800 )
                return "你在雪山派中碌碌无为，教我怎能放心传你绝技。";

        if (me->query_skill("force") < 150)
                return "你的内功修行太浅，练好了再来找我。";

  if (me->query_skill("jinwu-blade", 1) < 120)
                return "你的金乌刀法练成这样，居然还好意思找我。";

        message_vision( HIY "$n" HIY "道：“你能有今日这个地步，也"
                       "算不错。今日我\n传你雪山剑法的破解之法，你"
                       "可记牢了。雪山派剑法有\n七十二招，我金乌派"
                       "武功处处胜他一筹，却有七十三招。\n咱们七十"
                       "三招破他七十二招，最后一招瞧仔细了！”说\n"
                       "着拔出腰间柴刀从上而下直劈下来，又道：“你"
                       "使这招\n之时，须得跃起半空，和身直劈！”当"
                       "下又教将如何运\n劲，如何封死对方逃遁的空隙"
                       "等窍门慢慢传给$N" HIY "，$N" HIY "凝\n思半"
                       "晌，依法施为，纵身跃起，半空中挥刀直劈，呼"
                       "的\n一声，刀锋离地尚有数尺，地下已是尘沙飞"
                       "扬，败草落\n叶被刀风激得团团而舞，果然威力"
                       "惊人。\n" NOR, me, this_object());
        command("heng");
        command("say 这一招可尽破雪山剑法，你自己下去练吧。");
        tell_object(me, HIC "你学会了「赤焰暴长」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
 if (me->can_improve_skill("jinwu-blade"))
     me->improve_skill("jinwu-blade", 1500000);
        me->improve_skill("martial-cognize", 1500000);
  set("can_perform/jinwu-blade/chi", 1, me);
        addn("family/gongji", -800, me);
        return 1;
}
string ask_book()
{
        object me,ob;
        ob=this_player();

        if( query("family/master_id", ob) == "bai wanjian" )
        {
                if (query("count") == 1)
                {
                        command("say 你是万剑的弟子吗？那就给你吧。");
                        message_vision(HIG"史婆婆掏出一本小册子，交给$N。\n\n"NOR,ob);
                        me=new(BOOK_DIR+"jinwu-book");
                        me->move(ob);
                        addn("count", -1);
                        return "你好好读读，比老鬼的剑法好多了。\n";
                }
                else return"你来晚啦，刀谱已经让人拿走了。\n";
        }
        if( query("family/master_id", ob) == "bai zizai" )
        {
                if (query("count") == 1)
                {
                        command("say 你是老鬼的弟子吗？那就给你吧。");
                        message_vision(HIG"史婆婆掏出一本小册子，交给$N。\n\n"NOR,ob);
                        me=new(BOOK_DIR+"jinwu-book");
                        me->move(ob);
                        addn("count", -1);
                        return "你好好读读，比老鬼的剑法好多了。\n";
                }
                else return "你来晚啦，刀谱已经让人拿走了。\n";
        }

        command("say 走开，不然老太婆要发火了？");
        message_vision(HIG"史婆婆哼了一声，不理$N。\n\n"NOR,ob);

        return "我虽离开了凌霄城，却也不会乱传人武功。\n";
}

int recognize_apprentice(object ob)
{
        mapping myfam;
        myfam=query("family", ob);
        if ( !myfam || myfam["family_name"] == "凌霄城") return -1 ;
        if( query_temp("tmark/shi", ob) == 1 )
        message_vision("史婆婆哼了一声，对$N说道：老身今天不想再教了，你下次再来吧。\n", ob);
        if( !query_temp("tmark/shi", ob))return 0;
        addn_temp("tmark/shi", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        if( query("id", ob) == "jinwu zhang" )
        {
                if( !query_temp("tmark/shi", who) )
                        set_temp("tmark/shi", 0, who);
                message_vision("史婆婆接过金乌杖，“呵呵”笑了两声，摸摸杖身，说道：\n好！好！好！难得你帮我乖孙女办事，真不错，好吧！\n老身今天正好有空，就教你一会工夫吧。\n", who);
                addn_temp("tmark/shi", 900, who);
                return 1;
        }
        return 0;
}

string ask_skill()
{
        object me=this_object();
        object ob= this_player();

  if( query("can_perform/jinwu-blade/jinwu", ob) )
                return "你不是已经学会了吗，还找我做什么。";

        if( query("family/master_id", ob) != "shi popo" )
 return "你不是我的弟子，走开！";

    if ((int)ob->query_skill("jinwu-blade",1) < 100)
                return "你的金乌刀法还不到家，用不了这招。";

          if ((int)ob->query_skill("xueshan-neigong",1) < 100)
             return "你的雪山内功心法火候不够，用不了这招。";

        if( query("max_neili", ob)<1000 )
                return "你的内力还差一些，加油吧。";

        message_vision( HIY "$n" HIY "道：“你能有今日这个地步，也"
                       "算不错。今日我\n传你雪山剑法的破解之法，你"
                       "可记牢了。雪山派剑法有\n七十二招，我金乌派"
                       "武功处处胜他一筹，却有七十三招。\n咱们七十"
                       "三招破他七十二招，最后一招瞧仔细了！”说\n"
                       "着拔出腰间柴刀从上而下直劈下来，又道：“你"
                       "使这招\n之时，须得跃起半空，和身直劈！”当"
                       "下又教将如何运\n劲，如何封死对方逃遁的空隙"
                       "等窍门慢慢传给$N" HIY "，$N" HIY "凝\n思半"
                       "晌，依法施为，纵身跃起，半空中挥刀直劈，呼"
                       "的\n一声，刀锋离地尚有数尺，地下已是尘沙飞"
                       "扬，败草落\n叶被刀风激得团团而舞，果然威力"
                       "惊人。\n" NOR, ob, this_object());
        command("heng");
        tell_object(ob, HIC "你学会了「金乌坠地」。\n" NOR);
    set("can_perform/jinwu-blade/jinwu", 1, ob);
        return "这一招可尽破雪山剑法，你自己下去练吧。";
}
