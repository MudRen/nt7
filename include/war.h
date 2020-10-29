
// 蒙古军队进攻路线
protected mapping ward_way = ([
        "/d/city2/mying1"           :     "south",
        "/d/city2/mying"            :     "south",
        "/d/city2/myuanmen1"        :     "south",
        "/d/city2/caoyuan4"         :     "south",
        "/d/city2/caoyuan3"         :     "west",
        "/d/city2/caoyuan2"         :     "west",
        "/d/city2/caoyuan1"         :     "west",
        "/d/city2/caoyuan"          :     "west",
        "/d/city2/shanlu3"          :     "west",
        "/d/city2/dhunya"           :     "south",
        "/d/city2/shanlu2"          :     "south",
        "/d/city2/wsling"           :     "south",
        "/d/city2/shanlu1"          :     "south",
        "/d/city2/shanlu"           :     "south",
        "/d/city2/conglin1"         :     "south",
        "/d/city2/conglin2"         :     "south",
        "/d/city2/conglin3"         :     "west",
        "/d/city2/conglin4"         :     "west",
        "/d/city2/syuanmen1"        :     "south",
        "/d/city2/sying"            :     "south",
]);

// 侦察路线及烧粮路线
protected mapping forrecon_way = ([
        "/d/city2/mying6"            :     "north",
        "/d/city2/mying5"        :     "north",
        "/d/city2/caoyuan8"         :     "north",
        "/d/city2/caoyuan7"         :     "west",
        "/d/city2/caoyuan6"         :     "west",
        "/d/city2/caoyuan5"         :     "west",
        "/d/city2/caoyuan"          :     "west",
        "/d/city2/shanlu9"          :     "west",
        "/d/city2/shanlu8"           :     "north",
        "/d/city2/shanlu7"          :     "north",
        "/d/city2/shanlu6"           :     "north",
        "/d/city2/shanlu5"          :     "north",
        "/d/city2/shanlu4"           :     "north",
        "/d/city2/conglin5"         :     "northdown",
        "/d/city2/conglin2"         :     "northup",
        "/d/city2/conglin3"         :     "north",
        "/d/city2/conglin4"         :     "east",
        "/d/city2/syuanmen1"        :     "east",
        "/d/city2/sying"            :     "north",
        "/d/city2/sying1"           :     "north",
]);

protected mapping backrecon_way = ([
        "/d/city2/mying7"            :     "south",
        "/d/city2/mying6"            :     "south",
        "/d/city2/mying5"        :     "south",
        "/d/city2/caoyuan8"         :     "south",
        "/d/city2/caoyuan7"         :     "east",
        "/d/city2/caoyuan6"         :     "east",
        "/d/city2/caoyuan5"         :     "east",
        "/d/city2/caoyuan"          :     "east",
        "/d/city2/shanlu9"          :     "east",
        "/d/city2/shanlu8"           :     "south",
        "/d/city2/shanlu7"          :     "south",
        "/d/city2/shanlu6"           :     "south",
        "/d/city2/shanlu5"          :     "south",
        "/d/city2/shanlu4"           :     "south",
        "/d/city2/conglin5"         :     "southup",
        "/d/city2/conglin2"         :     "southdown",
        "/d/city2/conglin3"         :     "south",
        "/d/city2/conglin4"         :     "west",
        "/d/city2/syuanmen1"        :     "west",
        "/d/city2/sying"            :     "south",
]);

// 押运粮草、购置兵甲、购置箭羽、购置石木、购置战马、招募士兵路线
protected mapping forward_way = ([
        "/d/city2/sying1"           :     "south",
        "/d/city2/sying4"           :     "south",
        "/d/city2/syuanmen2"        :     "west",
        "/d/city2/yidao"            :     "west",
        "/d/xiangyang/eastgate2"            :     "west",
        "/d/xiangyang/eastgate1"            :     "west",
        "/d/xiangyang/eastjie3"             :     "west",
        "/d/xiangyang/eastjie2"             :     "west",
        "/d/xiangyang/eastjie1"             :     "west",
        "/d/xiangyang/guangchang"           :     "west",
        "/d/xiangyang/westjie1"             :     "west",
        "/d/xiangyang/westjie2"             :     "west",
        "/d/xiangyang/westjie3"             :     "west",
        "/d/xiangyang/westgate1"            :     "west",
        "/d/xiangyang/westgate2"            :     "west",
        "/d/city2/yidao1"       :     "west",
        "/d/city2/yidao2"       :     "west",
        "/d/city2/yidao3"       :     "north",
]);

protected mapping backward_way = ([
        "/d/city2/sying4"           :     "north",
        "/d/city2/syuanmen2"        :     "north",
        "/d/city2/yidao"            :     "east",
        "/d/xiangyang/eastgate2"            :     "east",
        "/d/xiangyang/eastgate1"            :     "east",
        "/d/xiangyang/eastjie3"             :     "east",
        "/d/xiangyang/eastjie2"             :     "east",
        "/d/xiangyang/eastjie1"             :     "east",
        "/d/xiangyang/guangchang"           :     "east",
        "/d/xiangyang/westjie1"             :     "east",
        "/d/xiangyang/westjie2"             :     "east",
        "/d/xiangyang/westjie3"             :     "east",
        "/d/xiangyang/westgate1"            :     "east",
        "/d/xiangyang/westgate2"            :     "east",
        "/d/city2/yidao1"       :     "east",
        "/d/city2/yidao2"       :     "east",
        "/d/city2/yidao3"       :     "east",
        "/d/city2/chengmen"     :     "south",
]);

protected string *ward_place = ({
        "/d/city2/sying2",
          "/d/city2/sying3",
            "/d/city2/sying1",
        "/d/city2/sying",
          "/d/city2/syuanmen1",
         "/d/city2/sying4",
});

protected string *degree_desc = ({
       HIC "裨将" NOR,
       HIY "佐将" NOR,
       HIY "副将" NOR,
       HIR "将军" NOR,
       HIR "提督" NOR,
       HIR "总督" NOR,
       MAG "兵部侍郎" NOR,
       MAG "兵部尚书" NOR,
       HIB "镇北节度使" NOR,
});