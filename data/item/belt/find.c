// cruise-ob.c

#include "/clone/misc/belt_ob.h"

string long() 
{
        string msg; 
        
        msg = query("long"); 
        msg += "这是寻宝小娘(find)的勋章挂带。
";
        
        //return sort_string(msg, 64, 0); 
        return msg;
}

void owner_is_killed() { destruct(this_object()); } 