#include <ansi.h>
#include <ansi.h>
inherit ITEM;
void create()
{
   set_name("养精丹", ({"yangjing dan", "dan"}));
   /*if (clonep())
      set_default_object(__FILE__);
   else*/ {
      set("unit", "粒");
      set("value", 2000);
   }
   setup();
}
int init()
{
   add_action("do_eat", "eat");
}
int do_eat(string arg)
{
   object me = this_player();
   if(!id(arg))
       return notify_fail("你要吃什么？\n");
   message_vision("$N吃下一粒" + name() + "。\n", me);
/*   if (((int)me->query_condition("xx_poison") > 0) ||
         (query("eff_jing", me)<query("max_jing", me))){
      me->apply_condition("jing_curing", me->query_condition("jing_curing")
         + 10);
*/
   if (((int)me->query_condition("xx_poison") > 0) ||
        ((query("eff_jing", me)/query("max_jing", me))<0.9)){
	this_player()->receive_curing("jing",query("max_jing", me)/50);
   }
   destruct(this_object());
   return 1;
}
int query_autoload() { return 1; }