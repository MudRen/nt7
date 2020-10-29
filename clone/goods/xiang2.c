
#include <ansi.h>
inherit BAOXIANG_ITEM;

void create()
{
        set_name(HIM"神秘箱子"NOR,({"xiang"}));
        //这个一定要设置：
        set("BAOXIANG_LIST",([
                "/d/emei/obj/pantao":900,   //物品文件名:概率
                "/clone/fam/max/zaohua":100,   //物品文件名:概率
        ])); //概率是以1000作为总数，且几项的概率总和为1000，概率大的出现几率高。。。
        
        set("long", HIY "这是一只金色的宝箱，上面篆刻着符文，你或许可以打开（open）它。\n" NOR); 
        set("unit", "些");
        set("base_unit", "个");
        set("no_give",1);
        set("no_drop",1);
        set("base_weight",1);
        set("base_value",1);
        set_amount(1); //因为是个combined物品 所以这个一定要设置，不然报错的

}
void init()
{
        add_action("do_open","open"); //玩家使用的接口 具体内容在std里
        add_action("do_test","test"); //用于巫师测试用 测试ok请注释此行
}

