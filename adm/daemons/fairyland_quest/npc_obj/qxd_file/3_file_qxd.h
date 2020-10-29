void create()
{
    set_name(long_color+"七星灯"NOR, ({"qixing deng","deng"}));
    set_weight(10);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", longs + get_deng_pic(DENG_AMOUNT) );
        set("unit", "个");
        set("value", 0);
    }

    set("no_drop","这东西是只属于你一个人的。\n");
    set("no_give","这东西是只属于你一个人的。\n");
    set("no_steal","这东西是只属于别人一个人的。\n");
    set("no_get","这东西不是你的，无法拾取。\n");
    set("lost_time",1);  // 本轮已过的时间(秒)
    set("last_deng",DENG_AMOUNT);  // 还剩几个灯
    set("no_updated_dest", 1 ); // 不让 updated 随机丢失

    set("hj_game/obj","qx_deng");

    setup();
}

void init()
{
    if(start_checking == 0)
    {
        start_checking = 1;
        remove_call_out("checking");
        call_out("checking",1);
    }
    add_action("do_ghp", ({ "ghp", "hh", }) );
    add_action("do_gi", ({ "gi", "ii", }) );
    add_action("do_gk", ({ "gkill", "kk", }) );
    add_action("do_gsks", ({ "gsks", "gskills", "ss", }) );
    add_action("do_gheal", ({ "gheal", "hl", }) );
    add_action("do_halt", ({ "ghalt", "ht", }) );
    add_action("do_gbei", ({ "gbei", "bb" }) );
    add_action("do_gpfm", ({ "gpfm", "pp",}) );
    add_action("do_gyun", ({ "gyun", "yy",}) );
    add_action("do_who_in_hj", ({ "gwho", "ww", }) );
    add_action("do_wizhg", "wizhg");
    add_action("do_hjtop", "hjtop", );
    add_action("do_hjtime", "hjtime");
    add_action("do_hjquit", "hjquit");    // 强制退出 huanjing 游戏的指令。
    add_action("do_hjleave", "hjleave", );   // 临时离开游戏 
}

int do_wizhg()
{
    object me = this_player();
    if( !wizardp(me) ) return 0;
    if( !me_ok(me) ) return 0;
    set("use_huigui","yes");
    message_vision( CYN"$N"NOR+CYN"大声叫道：“我是巫师，让我回家！！！”\n"NOR+WHT"只见一阵白雾不知从何处飘来，愈来愈浓……\n"NOR,me);
    return 1;
}

void checking()
{
    object ob,me,*all_mine,debuger;
    int temp,hp,i;

    time=query("lost_time", this_object());
    deng=query("last_deng", this_object());

//    write("checking.\n");

    ob=this_object();
    me=query("my_master");

    if( !me || !query_temp("huanjing", me) )
    {
        call_out("delete_me",1);
        return;
    }

    if( query_temp("huanjing", me) == "fail" || query_temp("huanjing", me) == "over" )
        return;

    if( query_temp("huanjing", me) == "feng"
          || query_temp("huanjing", me) == "yu"
          || query_temp("huanjing", me) == "lei"
          || query_temp("huanjing", me) == "dian" )
    {
        if ( singing == "no" )
        {
            singing = "yes";
            switch(query_temp("huanjing", me) )
            {
                case "feng":songs=context1;break;
                case "yu":songs=context2;break;
                case "lei":songs=context3;break;
                case "dian":songs=context4;break;
            }
            remove_call_out("sing_song");
            call_out("sing_song",1,0,me);
        }
        return;
    }

    hp=query_temp("hj_hp", me);
    if( !hp || hp < 1 )
    {
        all_mine = all_inventory(me);
        if(all_mine || sizeof(all_mine) > 0)
        {
            int mark, mark2;
            object room, env;
            if( (env=environment(me)) )
                mark=query("room_mark", env);
            for(i=sizeof(all_mine)-1; i>=0; i-- )
            {
                if( query("hj_game/obj", all_mine[i] )
                   && query("id", all_mine[i]) != "qixing deng"
                )
                {
                    if( random(5) )
                    {
                        if( mark > 0 && mark <= HJ_ROOM_AMOUNT && !random(3) )
                            mark2 = mark;
                        else
                            mark2 = 1+random( HJ_ROOM_AMOUNT );
                        if( !(room = find_object( HJ_DIR +"hj_room"+mark2 )) )
                            if( !(room = load_object( HJ_DIR +"hj_room"+mark2 )) )
                                room = env;
                        all_mine[i]->move(room);
                        if( room == env )
                            message_vision(sprintf("一%s%s似是从$N身上跳出来般，跌在了地上。\n",
                                query("unit", all_mine[i]),query("name", all_mine[i])),me);
                        else
                        {
                            message_vision(sprintf("一%s%s似是从$N身上跳出来般，往远处天空飞射而去！\n",
                                query("unit", all_mine[i]),query("name", all_mine[i])),me);
                            tell_room( room, sprintf("一%s%s突然从天上落了下来。\n",
                                query("unit", all_mine[i]),query("name", all_mine[i])));
                        }
                    }
                    else
                    {
                        destruct(all_mine[i]);
                    }
                }
            }
        }
        message_vision(HIR"$N"HIR"忽然两眼发直，不能动弹了！\n"NOR,me);
        me->start_busy(3);
        set_temp("huanjing", "fail", me);
        remove_call_out("game_over");
        call_out("game_over",1);
        debuger = find_player("lonely");
        if( debuger && query("env/hj_wizmsg", debuger) )
            tell_object( debuger, sprintf( HIR"幻境游戏通知：%s"HIR"(%s"HIR")失败状态离开了游戏。 ( <unset hj_wizmsg> 不再发送本类信息)\n"NOR,
        query("name", me),query("id", me)));
        CHANNEL_D->channel_broadcast("rumor", sprintf("幻境: 听说%s[%s]探险失败，离开了幻境。",query("name", me),query("id", me)));
        return;
    }

    time++;

    if( wait_over == "yes" && time > DENG_TIME / 5 )
    {
        me->start_busy(3);
        set_temp("huanjing", "over", me);
        remove_call_out("game_over");
        call_out("game_over",1);

        debuger = find_player("lonely");
        if( debuger && query("env/hj_wizmsg", debuger) )
            tell_object( debuger, sprintf( HIR"幻境游戏通知：%s"HIR"(%s"HIR")成功状态离开了游戏。 ( <unset hj_wizmsg> 不再发送本类信息)\n"NOR,
        query("name", me),query("id", me)));
        CHANNEL_D->channel_broadcast("rumor", sprintf("幻境: 听说%s[%s]探险成功，离开了幻境。",query("name", me),query("id", me)));
        return;
    }

    if( wait_over !="yes" && time > DENG_TIME )  // 时间到，结束游戏（ 不算 fail ）
    {
        if( EXTEND_DENG > 0 )
        {
            EXTEND_DENG--;
            if( EXTEND_DENG < 2 ) set("can_quit_hj", 1);
        }
        else
        {
            deng--;
            time=1;
            if(deng < 1)  // 灯全灭后，还有一点点时间。
            {
                wait_over = "yes";
                set("wait_over","yes");
            }

            if( deng > 0 )
                message_vision("$N只听得似有一声微响，只见"+query("name", ob)+"里的一个亮点熄灭了。\n",me);
            else message_vision("$N只听得似有一声微响，只见"+query("name", ob)+"里的最后一个亮点也熄灭了。\n",me);


            tell_object( me, get_deng_pic( deng ) );

            if(deng == 4) long_color=""HIB"";
            if(deng == 2) long_color=""BLU"";
            longs="这是一个四四方方的小盒子，盒盖透明，你能见到内里有"+long_color+chinese_number(deng)+"个小点"NOR"在散发着微弱的光芒。\n";
            set_name(long_color+"七星灯"NOR, ({"qixing deng","deng"}));
            if( deng > 0 ) set("long",longs + get_deng_pic(deng) );
            else set("long",BLU"这是一个四四方方的小盒子，盒盖透明，里面已经一丝亮光也见不到了。\n"NOR  + get_deng_pic(deng) );
        }
    }

    // 随机让别的玩家看到自己大概的状态(虚拟游戏里也有PK哦)
    // 玩家若暂时离开游戏，则不报告
    if( !present( "hj temp leave obj", me ) )
    {
        if( query_temp("hj_hp", me)<(query_temp("hj_hp_max", me)*2/10) )
        {
            if( random(10) == 1) 
                tell_room(environment(me),
                    RED+query("name", me)+""RED"一副头重脚轻的样子，看来就要支持不住了。\n"NOR,({me}));
        }
        else if( query_temp("hj_hp", me)<(query_temp("hj_hp_max", me)*4/10) )
        {
            if( random(10) == 1) 
                tell_room(environment(me),
                    HIR+query("name", me)+""HIR"受伤甚为严重，堪堪就要倒下似的。\n"NOR,({me}));
        }
        else if( query_temp("hj_hp", me)<(query_temp("hj_hp_max", me)*6/10) )
        {
            if( random(10) == 1) 
                tell_room(environment(me),
                    HIY+query("name", me)+""HIY"似乎受了伤，看起来状况不大好。\n"NOR,({me}));
        }
    }
    // 这里为了回归之镜的。
    if( query("use_huigui", this_object()) )
    {
        wait_over = "yes";
        time = DENG_TIME ;
    }
    // 得分 500+ 时，随机掉分。这是为了让玩家更紧凑地抓紧时间。
    // 恢复之技特殊技能“克制”的唯一体现，不掉分
    if( query_temp("hj_score", me)>500 && !random(3) && !query_temp("hj_special/kz", me) )
    {
        // 玩家临时离开时，减分的速度较慢
        if( !present( "hj temp leave obj", me ) || !random(3) )
            addn_temp("hj_score", -1, me);
    }
    set("lost_time",time);
    set("last_deng",deng);
    // 更新后的走路忙时系统，配合房间里的增加busy语句，这里就减少。
    addn_temp("hj_move_busy", -300, me);
    if( query_temp("hj_move_busy", me)<1 )
        set_temp("hj_move_busy", 1, me);

    remove_call_out("checking");
    call_out("checking",1);
}

void game_over()
{
    object me=query("my_master");
    int enter_time;
    if( !me || !query_temp("huanjing", me) )
    {
        call_out("delete_me",1);
        return;
    }
    message_vision(HIR"$N"HIR"突然一副灵魂出窍的样子，紧接着消失不见了。\n"NOR,me);
    me->move( HJ_OUT_ROOM );
    message_vision(HIR"$N"HIR"身影逐渐显现，似是回到现实里来了。\n"NOR,me);
    enter_time=query_temp("hj_enter_time", me);
    write(sprintf( "你进入游戏的时间是 %s ，结束的时间是 %s ，\n游戏时间%s 。\n",
        !enter_time ? "未知" : ctime_format( enter_time ),  ctime_format(),
        !enter_time ? "未知" : sprintf( "共 %d 小时 %d 分 %d 秒", 
            ( time() - enter_time ) / 3600,
            ( ( time() - enter_time ) % 3600 ) / 60,
            ( ( time() - enter_time ) % 3600 ) % 60 ) ) );
    set_temp("hj_out_time", time(), me);
}

void sing_song(int i, object me)
{
    if( !me || !query_temp("huanjing", me) )
    {
        call_out("delete_me",1);
        return;
    }

    singing="yes";

    if (i<sizeof(songs))
    {
        if(i==0) message_vision(CYN"$N忽地似乎感到一阵歌声又在耳边响起，不禁凝神细听起来。\n"NOR,me);
        else write(MAG"   "+songs[ i ] + "\n"NOR);
        i ++;
        remove_call_out("sing_song");
        call_out("sing_song",1,i, me);
    }
    else
    {
        set_temp("huanjing", "start", me);
        message_vision(CYN"你听得声音渐弱，终于静止下来了。\n"NOR,this_object());
        write("\n在灯灭之后，就是你归来之时……若你气息(ghp)已无，就将失败而归……\n");
        write(HIW"在幻境里，你只能使用特别的指令来进行攻击。详细请用 <help huanjing> 指令查询。\n"NOR);
        remove_call_out("enter_hj");
        call_out("enter_hj",1);
    }
}

void enter_hj()
{
    object me,rooms,srl,debuger;

    string random_rooms, *key;
    int i, temp_int;
    mapping temp_map1, temp_map2;

    me = query("my_master");
    if( !me || query_temp("huanjing", me) != "start" )
    {
        call_out("delete_me",1);
        return;
    }

    random_rooms= HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
    message_vision(HIR"$N"HIR"踏步走出，忽然间感到一阵强烈的震荡！……\n"NOR,me);
    rooms = load_object(random_rooms);

    // 若玩家身上有游戏内的标记，清除。
    delete_temp("hj_move_busy", me);
    delete_temp("hj_find_ok", me);
    delete_temp("hj_need_waiting", me);
    delete_temp("hj_game_skills", me);
    delete_temp("hj_game_damages", me);
    delete_temp("hj_find_gem", me);
    delete_temp("hj_quest_answer", me);
    delete_temp("hj_healing", me);
    delete_temp("hj_fighting", me);
    delete_temp("hj_special", me);
    delete_temp("hj_youling_job", me);
    delete_temp("hj_out_time", me);
    delete_temp("this_time_mark", me);

    // 清除完毕才能进入游戏。
    // ###################################################
    // ###############  设置玩家各类信息  ################
    // ###################################################
    // 新加入的“等级”设置
    // 每1 lv，都能够得到 0.5 power, 1 all skills, 20 hp_max 的进入加成。
    // lv 最低0级，最高9级。9级时，额外 +1。升级规则请参看 hj_room1.c .
    // lv 与本文件的“使用累积次数”部分有联系，请参看下文。
    if( !query("huanjing2003/lv", me) )
        set("huanjing2003/lv", 0, me);
    if( query("huanjing2003/lv", me)>9 )
        set("huanjing2003/lv", 9, me);
    // lv 加成
    if( query("huanjing2003/lv", me) == 9 )
        set("huanjing2003/lv_add", 10, me);
    else
        set("huanjing2003/lv_add",query("huanjing2003/lv",  me), me);
    // 进入时间
    set_temp("hj_enter_time", time(), me);
    // 得分，这个是游戏结束后重要奖励依据之一，在游戏里由各种途径增加
    set_temp("hj_score", 1, me);
    // 这是玩家在战斗是将使用的方式的判断！由本目录 6_combat_qxd.h 内调用。
    set_temp("hj_bei", ".", me);
    // 取个随机数做标记，该标记将判断：某个组合好的宝物是否是该玩家在这一次
    // 游戏里得到的。如果不是，得分要打个折扣。
    // 这是在测试活动时，出现了这样的情况：几个玩家配合，其中一个拿到组合宝物
    // 之后直接 huigui 甚至是 hjquit fail，由于以前的设置是不让组合宝物 checking()，
    // 所以玩家可以把宝物攒起来，到一定程度后一次过带出去，以求高记录和高效率。
    // 这个问题不改也行，不过对于统计数字来说，有点吓人。还是改改吧。 :)
    set_temp("this_time_mark", 1+random(9999), me);
    // 力量、气息以及技能，将在后面设置。
    // 基本设置完毕，为了描述更为显眼，先将玩家 move room，
    // 再进行特别的判断，并且显示特别信息。那样一来，这些
    // 特别的信息就不会被 room 的 long 冲掉。
    me->move(rooms);
    tell_object(me,"\n");
    // 接下来是特别的处理。玩家在退出游戏时，进行了登记的话，无论
    // 成功与否，都会更新 "last_skills" 以及 "last_power" 。
    // 玩家可以选择奖品项目“技能保留”、“力量保留”来继续使用这些设置。
    // 技能保留限制：原等级 4/5，最高80级（即防BUG限制）！最低 LV 0，即遗忘该技能。
    // 力量保留限制：原力量 3/4，并且最高 30，最低 5。
    // 现在，先把上一次的记录降低。玩家如果在游戏中非法退出，或者
    // 不登记成绩就退出，即得不到提升，只能越降越低，直至被取消。
    // 降低 last_power .
    if( query("huanjing2003/last_power", me) )
    {
        set("huanjing2003/last_power",query("huanjing2003/last_power",  me)*3/4, me);
        if( query("huanjing2003/last_power", me)>30 )
            set("huanjing2003/last_power", 30, me);
    // 如果太低，清除它。这里与 lv 无关。
        if( query("huanjing2003/last_power", me)<6 )
            delete("huanjing2003/last_power", me);
    }
    // 降低 last_skills .
    if( query("huanjing2003/last_skills_name", me )
       && mapp(query("huanjing2003/last_skills_name", me) )
       && sizeof(query("huanjing2003/last_skills_name", me)) >= 1
       && query("huanjing2003/last_skills_lv", me )
       && mapp(query("huanjing2003/last_skills_lv", me) )
       && sizeof(query("huanjing2003/last_skills_name", me)) >= 1 )
    {
        temp_map1=query("huanjing2003/last_skills_lv", me);
        temp_map2 = ([]);

        key = keys( temp_map1 );
        // 检测是否有该名字的 skills. 如果有，该 skills 通过，可以加入处理列表中。
        for( i=0; i<sizeof(key); i++ )
        {
            if( !undefinedp(query("huanjing2003/last_skills_name", me)[key[i]]) )
            {
                temp_int = temp_map1[key[i]] *4/5;
                if( temp_int > 80 ) temp_int = 80;
                if( temp_int ) temp_map2 += ([ key[i] : temp_int ]);
                else delete("huanjing2003/last_skills_name/"+key[i], me);
            }
        }

        // 设置降低后的技能列表。
        set("huanjing2003/last_skills_lv", temp_map2, me);
    }
    // 如前边的众多条件有任一不符，清理掉它们，避免未知的非法情况。
    else
    {
        delete("huanjing2003/last_skills_name", me);
        delete("huanjing2003/last_skills_lv", me);
    }
    // ok! 下面进行次数判断，如果玩家有有效使用次数，则可以
    // 使用这些上一次的技能及力量。
    // 否则设置基本数值。
    if( query("huanjing2003/last_power_times", me) )
    {
        if( !query("huanjing2003/last_power", me) )
        {
            tell_object(me,sprintf("你还可以使用%d次累积力量，但是现在你的累积力量比你能得到的基本力量还低，并未生效。\n",query("huanjing2003/last_power_times", me)));
            set_temp("hj_game_mepower", 5, me);
        }
        else
        {
            addn("huanjing2003/last_power_times", -1, me);
            tell_object(me, sprintf("你使用了累积力量的奖励，该奖励还剩余 %d 次。\n",
                query("huanjing2003/last_power_times", me)));
            set_temp("hj_game_mepower",query("huanjing2003/last_power",  me), me);
        }
    }
    else
        set_temp("hj_game_mepower", 5, me);
    // 是否有技能保留次数
    if( query("huanjing2003/last_skills_times", me) )
    {
        if( !query("huanjing2003/last_skills_lv", me) )
        {
            tell_object(me,sprintf("你还可以使用%d次累积技能，但是现在你没有任何累积技能，并未生效。\n",query("huanjing2003/last_skills_times", me)));
            set_temp("hj_game_skills/heal", "恢复之技", me);
            set_temp("hj_game_damages/heal", 3+random(8), me);
        // 默认设置为只懂得 heal.
        }
        else
        {
            addn("huanjing2003/last_skills_times", -1, me);
            tell_object(me,sprintf("你使用了累积技能的奖励，该奖励还剩余 %d 次。\n",
                query("huanjing2003/last_skills_times", me)));
            set_temp("hj_game_damages",query("huanjing2003/last_skills_lv",  me), me);
            set_temp("hj_game_skills",query("huanjing2003/last_skills_name",  me), me);
        }
    }
    // 否则设置默认技能。
    else
    {
        set_temp("hj_game_skills/heal", "恢复之技", me);
        set_temp("hj_game_damages/heal", 3+random(8), me);
    }
    if( 1 )
    {
        mapping find_name = ([
            "feng" : HIW"风之国度"NOR,
            "yu"   : HIM"雨之国度"NOR,
            "lei"  : HIC"雷之国度"NOR,
            "dian" : HIG"电之国度"NOR,
        ]);
        set_temp("apply/short",({sprintf("%s%s(%s)"NOR,
            find_name[ query_temp( "hj_game_find", me) ],
            query("name", me), capitalize(query("id",me)) ), }), me
        );
        set_temp("hj_apply_short", 1, me);
    }
    // 设置最大气息（原来的可以累积最大气息的设置已取消）
    set_temp("hj_hp_max", MAX_HP, me);
    // 下面进行 lv 加成设置。
    temp_int=query("huanjing2003/lv_add", me);
    // 在 lv 9 时，力量可自动保持为 20 点
    addn_temp("hj_game_mepower", temp_int/2, me);
    addn_temp("hj_hp_max", temp_int*20, me);
    // 在 lv 9 时，气息为 700
    key=keys(query_temp("hj_game_damages", me));
    for( i=0;i<sizeof(key);i++ )
        addn_temp("hj_game_damages/"+key[i], temp_int, me);
    // 在 lv 9 时，技能可自动保持为 50 级

    // 全部设置完毕，还有额外的其他奖励。
    // 破了记录或者是幸运玩家，有一定的 max_hp 奖励。
    if( query("huanjing2003/gift", me) )
    {
        tell_object(me,HIW"你曾是幻境游戏的"+query("huanjing2003/gift", me)+"者！\n你将得到增多300点游戏内最大气息、力量增强10点的奖励！\n"NOR);
        delete("huanjing2003/gift", me);
        addn_temp("hj_hp_max", 300, me);
        addn_temp("hj_game_mepower", 10, me);
    }
    // 雷之国度主动技能效果  气息增强。这个增强在最后才增强。
    if( query_temp("hj_game_find", me) == "lei" )
        addn_temp("hj_hp_max", (query_temp("hj_hp_max", me)/10), me);
    if( query_temp("hj_hp_max", me)>1500 )
        set_temp("hj_hp_max", 1500, me);
    set_temp("hjleave_usetimes", 0, me);//hjleave指令可以让玩家临时离开时保护角色的安全
    // 所有设置完毕。设置 hp，接下来可以进入游戏了。
    set_temp("hj_hp",query_temp("hj_hp_max",  me), me);
    // 得到一些必须的道具
    // 进入游戏时，有一个 120秒 的神人令。
    srl=new(__DIR__"shenren_ling");
    srl->waiting_delete( 120 );
    srl->move(me);
    tell_object(me,"你得到一"+query("unit", srl)+query("name", srl)+"！\n");

    // 进入游戏时，有一个 脱离水晶。( 这里使用了同样的变量名 )
    srl=new(__DIR__"hj_obj_tools");
    srl->setme(2);
    srl->move(me);
    tell_object(me,"你得到一"+query("unit", srl)+query("name", srl)+"！\n");

    // 有一个定向水晶
    srl=new(__DIR__"hj_obj_tools");
    srl->setme(0);
    srl->move(me);
    tell_object(me,"你得到一"+query("unit", srl)+query("name", srl)+"！\n");

// 此为关键物品，不再发放。
// 进入游戏时，有一个 回归之镜。
/*
    srl=new(__DIR__"hj_obj_tools");
    srl->setme(3);
    srl->move(me);
    tell_object(me,"你得到一个"+query("name", srl)+"！\n");
*/

    // 接受玩家 tianya 的提议，不再强制取消玩家的收听权。
    //    tell_object(me,HIB"你忽地觉得一片寂静，刚才的声音丝毫都听不见了。\n"NOR);
    //    if(!wizardp(me)) me->delete("channels");

    debuger = find_player("lonely");
    if( debuger && query("env/hj_wizmsg", debuger) )
        tell_object( debuger, sprintf( HIR"幻境游戏通知：%s"HIR"(%s"HIR")进入幻境游戏。 ( <unset hj_wizmsg> 不再发送本类信息)\n"NOR,
            query("name", me),query("id", me)));

    CHANNEL_D->channel_broadcast("rumor", sprintf("幻境: 听说%s[%s]进入了幻境，开始探险。",query("name", me),query("id", me)));
    remove_call_out("checking");
    call_out("checking",1);
    remove_call_out("random_dispersion");
    call_out("random_dispersion",1);
    remove_call_out("robot_check");
    call_out("robot_check", 180 + random(420) );

    me->save();
    return;
}

void delete_me()
{
    message_vision("$N忽地消失不见了。\n",this_object());
    destruct(this_object());
}

void real_random_dispersion()
{
    string random_rooms,msg;
    object obj,obj_me1,obj_me2,obj_me3,npc_ashman,rooms,me;
    int i;

    me=query("my_master");
    if( !me || query_temp("huanjing", me) != "start" || query_temp("hj_hp", me)<1 )
        return;
    msg="忽然一小阵轻烟掠过……这里似乎多了一些什么。\n";
    // 如果玩家是离开状态，那就不额外发放东西。
    if( !present( "hj temp leave obj", me ) )
    {
        // 发放 1-3 个随机物品(包括各类NPC)至随机房间。
        i = 1 + random(3);
        while( i-- )
        {
            random_rooms = HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
            rooms = find_object(random_rooms);
            if(!rooms) rooms = load_object(random_rooms);
            obj=new( obj_list_all[random(sizeof(obj_list_all))] );
            obj->move(rooms);
            if( query("msg", obj))msg=query("msg", obj);
            else msg="忽然一小阵轻烟掠过……这里似乎多了一些什么。\n";
            tell_room(random_rooms,msg);
        }
        random_rooms = HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
        rooms = find_object(random_rooms);
        if(!rooms)
            rooms = load_object(random_rooms);
        // 随机发放清道夫，即小矮人。
        // 小矮人停留时间更短了。
        i=1+random(2);
        while( i-- )
        {
            if( random(2) )
            {
                npc_ashman = new( __DIR__"hj_npc_ashman");
                npc_ashman->move(rooms);
                if( query("msg", npc_ashman))msg=query("msg", npc_ashman);
                else msg="忽然一小阵轻烟掠过……这里似乎多了一些什么。\n";
                tell_room(random_rooms,msg);
            }
        }
        if( !random(5) )  // 为了情节紧凑，将会发放更多的杀戮型NPC进入游戏
        {
            npc_ashman=new(__DIR__"hj_npc_kill");
            npc_ashman->move(rooms);
            if( query("msg", npc_ashman))msg=query("msg", npc_ashman);
            else msg="忽然一小阵轻烟掠过……这里似乎多了一些什么。\n";
            tell_room(random_rooms,msg);
        }
    }
    // 发放与本人选择有关的物品至随机房间。
    if( about_me_obj == 0 )
    {
        about_me_obj=1;
        switch(query("find_name", this_object()) )
        {
            case "风之国度":
                obj_me1=new( obj_list_feng[0] );
                obj_me2=new( obj_list_feng[0] );
                obj_me3=new( obj_list_feng[1] );
                break;
            case "雨之国度":
                obj_me1=new( obj_list_yu[0] );
                obj_me2=new( obj_list_yu[0] );
                obj_me3=new( obj_list_yu[1] );
                break;
            case "雷之国度":
                obj_me1=new( obj_list_lei[0] );
                obj_me2=new( obj_list_lei[0] );
                obj_me3=new( obj_list_lei[1] );
                break;
            case "电之国度":
                obj_me1=new( obj_list_dian[0] );
                obj_me2=new( obj_list_dian[0] );
                obj_me3=new( obj_list_dian[1] );
                break;
        }

        // 这几句的次序不能乱
        set("host_id",query("id",  me), obj_me1);
        obj_me1->setme(1);
        set("host_id",query("id",  me), obj_me2);
        obj_me2->setme(2);
        set("host_id",query("id",  me), obj_me3);//此为NPC，拿着最重要的物品部分

        random_rooms = HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
        rooms = find_object(random_rooms);
        if(!rooms) rooms = load_object(random_rooms);
        obj_me1->move(rooms);
        if( query("msg", obj_me1))msg=query("msg", obj_me1);
        else msg="忽然一小阵轻烟掠过……这里似乎多了一些什么。\n";
        tell_room(random_rooms,msg);

        random_rooms = HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
        rooms = find_object(random_rooms);
        if(!rooms) rooms = load_object(random_rooms);
        obj_me2->move(rooms);
        if( query("msg", obj_me2))msg=query("msg", obj_me2);
        else msg="忽然一小阵轻烟掠过……这里似乎多了一些什么。\n";
        tell_room(random_rooms,msg);

        random_rooms = HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
        rooms = find_object(random_rooms);
        if(!rooms) rooms = load_object(random_rooms);
        obj_me3->move(rooms);
        if( query("msg", obj_me3))msg=query("msg", obj_me3);
        else msg="忽然一小阵轻烟掠过……这里似乎多了一些什么。\n";
        tell_room(random_rooms,msg);
    }
}
// 不断地往游戏中添加物件
void random_dispersion()
{
    remove_call_out("random_dispersion");
    real_random_dispersion();
    call_out("random_dispersion", 60 + random(60) );
}
    
void real_robot_check()
{
    object checker, me;

    me=query("my_master");
    if( !me || query_temp("huanjing", me) != "start" || query_temp("hj_hp", me)<1
       || !environment(me) || !query("room_mark", environment(me) )
       || !query_temp("this_time_mark", me )
      || present( "hj temp leave obj", me )   // 临时离开游戏，不发放 robot
    )
        return;
    checker = new( __DIR__"hj_robot_checker" );
    set("checking_player", me, checker);
    set("this_time_mark",query_temp("this_time_mark",  me), checker);
    checker ->move( environment(me) );
    checker ->start_check();
}
// robot 检测程序，由另一个文件配合。
void robot_check()
{
    remove_call_out("robot_check");
    real_robot_check();
    call_out("robot_check", 600 + random(600) );
}
