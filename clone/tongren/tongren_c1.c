
#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "冲穴铜人·阴维脉·府舍穴" NOR, ({ "tongren c1", "tongren" }));
        set_weight(50);
        
        set("unit", "个");
        set("long", NOR + YEL "这是一个冲穴铜人，上面绘制了一些经络穴位图案，以及冲穴使用方法。\n" NOR);
        set("value", 10000);
        set("material", "steal");

        set("jingmai_name", "阴维脉");
        set("xuewei_name", "府舍穴");
        set("chongxue_xiaoguo", "NEI:120");
        set("neili_cost", "800");
        setup();
}


