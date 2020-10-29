// map.c
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( HIC "『天下旅游图』" NOR, ({ "luyou tu", "tu" }) );
        set_weight(10);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "张");
                set("long", @TEXT
                 『天下旅游图』
                                                                         天池
                                                                     长白山●/
                                                              赫图阿拉⊙ ▲ /
                                                                            /
                             ◎                                     ｏ宁远  /
 灵鹫峰                     灵州  黄  河                      山海关  _/-\ /
  ∧∧ 天山山脉                  ≈≈≈≈         八达岭    凸凸凹  _/   |/
   ∧∧∧ｏ∧∧  ∷嘉峪关≈≈≈ ≈      §          凹凸凸凸凹    _/  ～ ～
星宿海§ 伊犁  ∷∷凹凸凸凸   ≈         §   凹凸凸凸 京城   ___/ ～ ～ ¤ ～
         ∷∷∷∷∷∷∷∷∷ 凹凸凸凸     凹凸凸凸平定州 ⊙ ♀/ ～ ～～神龙岛～
白驼山  ∷∷大∷∷∷∷漠∷∷∷∷   凹凸凸凸§  △  ｏ    塘沽\___ ～ ～～ ～
  △  ∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷       §黑木崖 ▲恒山   ≈≈\_/---+__
∷∷∷∷∷∷∷∷∷     ｏ        ◎  华山村§             ≈≈ 泰山    __/
 ∷∷∷∷∷∷∷       兰州      永登   ｏ▲§中条山▲ ≈≈≈    ▲   _/   ～
∧∧  昆 仑 山 脉           长安◎      华山≈≈≈≈≈  汝州       _/ ～ ～
    ∧∧∧ ∧∧∧ ∧∧           ▲终南山                ｏ        |__  ～～
                             汉中ｏ ｏ         ▲嵩山       扬州    \_  ～
                                  函谷关            ｏ南阳   ◎ ≈苏州\_～
  青   藏   高   原                         ▲    ◎      无锡◎≈◎≈|_～
                    ∧                    武当山 襄阳       ≈≈   嘉兴♀| ～～ 
∧                   ∧   青城山  成都     荆州ｏ≈      ≈≈  杭州◎--_『～¤ 
  _∧∧             大雪山   ▲     ◎       ≈≈  ≈≈≈≈        ●   / 桃花岛
   \___∧∧           ∧       峨嵋山     ≈≈ 长      江         西湖  | ～
       \____∧∧       ∧≈      ▲    ≈≈                            _/ ～
  ＊注释   \_ ∧ ∧       §        ≈≈         衡山         ∧       |  ～
             -__--\        ≈    ≈≈   △        ▲     武夷∧ ｏ 福州| ～
  ⊙  首都         | 大理   ≈≈≈   摩天崖      ｏ衡阳 山脉∧ 延平 ◎/  ～
  ◎  城市       _/ ▲◎ ●滇池                                      /～台湾_
  ｏ  小镇       |_苍山 ｏ喜州                南岭∧∧ ∧∧  泉州♀_/～～ / |
  ∧  山川         |_   无量山                        佛山       _/～¤～/  |
△▲  高山           \_   △  ___                      ◎       / ～澎湖～\/
§≈  江河             |_  _--  \__                 渔村♀___---  ～ ～  ～
  ～  大海               \_|       \__              ___---  ～ ～～ ～～～～
  ∷  沙漠                            \__--\  ___--- ～ ～～～ ～～ ～～
  ♀  港口                            / ～ | /  ～～ ～～～  ～ ～～ ～～
  ¤  岛屿                            | ～  \| ～～～  ～～ ～ ～～～ ～～～
  凹  长城                           / ～ ～__--_～ ～ 侠客岛～～～ ～ ～～～
  ●  湖泊                           | ～  /    /～～ ¤～ ～～～ ～ ～～～～
                                    /   ～ --__-  ～ ～～～ ～～～～ ～～～
TEXT);
                set("value", 50);
                set("material", "paper");
        }
        setup();
}