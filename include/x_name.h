//物品
mapping weapon_file =
([
        "sword"  : "/clone/weapon/gangjian",   //钢剑
        "blade"  : "/clone/weapon/gangdao",    //钢刀
        "hammer" : "/clone/weapon/falun",      //法轮
        "staff"  : "/clone/weapon/gangzhang",  //钢杖
        "whip"   : "/clone/weapon/changbian",  //长鞭
]);

//色彩
string *all_color =
({
        "$WHT$", "$YEL$", "$MAG$", "$CYN$", "$BLU$", "$GRN$", "$RED$",
        "$HIW$", "$HIY$", "$HIM$", "$HIC$", "$HIB$", "$HIG$", "$HIR$",
});

//中缀
mapping name_a =
([
        /*
        "错筋" : "cuojin",
        "化骨" : "huagu",
        "碎心" : "suixin",
        "损精" : "sunjing",
        "吸血" : "xixue",
        */
        "幽溟" : "youming",
        "雷鸣" : "leiming",
        "涅磐" : "niepan",
        "紫阳" : "ziyang",
        "赤阴" : "chiyin",
        "裂天" : "lietian",
        "摄魂" : "shehun",
        "摩罗" : "moluo",
        "火阳" : "huoyang",
        "缤天" : "bintian",
        "钧天" : "juntian",
        "龙炎" : "longyan",
        "赤霞" : "chixia",
        "青虹" : "qinghong",
        "帝阙" : "dique",
        "古月" : "guyue",
        "伏魔" : "fumo",
        "离火" : "lihuo",
        "修罗" : "xiuluo",
        "星月" : "xingyue",
        "追魂" : "zhuihun",
        "混天" : "huntian",
        "混元" : "hunyuan",
        "追魂" : "zhuihun",
        "夺命" : "duoming",
//////////////////////////////
        "失神" : "shishen",
        "炽日" : "zhiri",
        "弑神" : "shishen",
        "怜星" : "lianxing",
        "无神" : "wushen",
        "邀月" : "yaoyue",
        "噬魔" : "shimo",
        "月霞" : "yuexia",
        "除魔" : "chumo",
        "神风" : "shenfeng",
        "空绝" : "kongjue",
        "月洁" : "yuejie",
        "风行" : "fengxing",
        "凌风" : "lingfeng",
        "飞花" : "feihua",
        "逐月" : "zhuyue",
        "飘星" : "piaoxing",
        "炫星" : "xuanxing",
        "蝶舞" : "diewu",
        "空寂" : "kongji",
        "飘月" : "piaoyue",
        "灵风" : "lingfeng",
        "梦神" : "mengshen",
        "断情" : "duanqing",
        "追星" : "zhuixing",
        "灵慧" : "linghui",
        "傲雪" : "aoxue",
        "吟龙" : "yinlong",
        "残月" : "canyue",
        "定风" : "dingfeng",
        "浩光" : "haoguang",
        "情义" : "qingyi",
        "毫光" : "haoguang",
        "灵星" : "lingxing",
        "七星" : "qixing",
        "断月" : "duanyue",
        "追云" : "zhuiyun",
        "豪情" : "haoqing",
        "剑心" : "jianxin",
        "凌云" : "lingyun",
        "龙形" : "longxing",
        "断脉" : "duanmai",
        "绝情" : "jueqing",
        "破空" : "pokong",
        "斩魔" : "zhanmo",
        "乾坤" : "qiankun",
        "鸿星" : "hongxing",
        "断空" : "duankong",
        "掠影" : "lueying",
        "幻影" : "huanying",
        "谰星" : "lanxing",
        "滚龙" : "gunlong",
        "飘雪" : "piaoxue",
        "覆雨" : "fuyu",
        "翻云" : "fanyun",
        "降魔" : "xiangmo",
        "秋寒" : "qiuhan",
        "电光" : "dianguang",
        "风雷" : "fenglei",
        "蔽日" : "biri",
        "幻魔" : "huanmo",
        "虚冥" : "xumi",
        "幽明" : "youming",
        "溟神" : "mingshen",
        "炎狱" : "yanyu",
        "焰心" : "yanxin",
        "风影" : "fengying",
        "偃月" : "yanyue",
        "雁行" : "yanxing",
        "龙蛇" : "longshe",
        "灵蛇" : "lingshe",
        "渺空" : "miaokong",
        "曜星" : "yaoxing",
        "望空" : "wangkong",
        "尘心" : "chenxin",
        "幻月" : "huanyue",
        "绝尘" : "juechen",
        "长恨" : "changhen",
        "驰风" : "chifeng",
        "天行" : "tianxing",
        "天罡" : "tiangang",
        "地煞" : "disha",
        "蛟龙" : "jiaolong",
        "龙神" : "longshen",
        "长空" : "changkong",
        "噬谷" : "shigu",
        "风刃" : "fengren",
        "寒光" : "hanguang",
        "定心" : "dingxin",
        "幻舞" : "huanwu",
        "翌日" : "yiri",
        "古锭" : "guding",
        "天玄" : "tianxuan",
        "太极" : "taiji",
        "天风" : "tianfeng",
        "无极" : "wuji",
////////////////////////////////
        "沉水" : "chenshui",
        "赤焰" : "chiyan",
        "荡寇" : "dangkou",
        "彗月" : "huiyue",
        "照夜" : "zhaoye",
        "追日" : "zhuiri",
        "断阙" : "duanque",
        "刑天" : "xingtian",
        // 机杼、苍野、青幽、百战、鬼烈、巨灵、深罡、九日
        // 恶来、玄狐、洛神、盘瓠、儵忽、帝江、烛阴、盘古
]);

//前缀
mapping name_b =
([
        "冰心" : "bingxin",
        "寒月" : "hanyue",
        "玄天" : "xuantian",
        "雪蝉" : "xuechan",
        "青璃" : "qingli",
        "紫焰" : "ziyan",
        "太玄" : "taixuan",
        "烈焰" : "lieyan",
        "贯日" : "guanri",
        "破月" : "poyue",
        "青龙" : "qinglong",
        "白虎" : "baihu",
        "朱雀" : "zhuque",
        "玄武" : "xuanwu",
        "盘古" : "pangu",
]);
