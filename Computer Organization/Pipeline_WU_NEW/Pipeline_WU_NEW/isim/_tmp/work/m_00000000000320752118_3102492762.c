/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2007 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/

/* This file is designed for use with ISim build 0x734844ce */

#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "C:/Users/wuxy3/Desktop/Pipeline_WU_NEW/DetectUnit.v";
static int ng1[] = {0, 0};
static int ng2[] = {1, 0};



static void A37_0(char *t0)
{
    char t5[8];
    char t19[8];
    char t34[8];
    char t50[8];
    char t65[8];
    char t73[8];
    char t101[8];
    char t109[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    char *t16;
    char *t17;
    char *t18;
    char *t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    char *t35;
    char *t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    char *t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    unsigned int t46;
    char *t47;
    char *t48;
    char *t49;
    char *t51;
    char *t52;
    unsigned int t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    char *t66;
    char *t67;
    unsigned int t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t72;
    unsigned int t74;
    unsigned int t75;
    unsigned int t76;
    char *t77;
    char *t78;
    char *t79;
    unsigned int t80;
    unsigned int t81;
    unsigned int t82;
    unsigned int t83;
    unsigned int t84;
    unsigned int t85;
    unsigned int t86;
    char *t87;
    char *t88;
    unsigned int t89;
    unsigned int t90;
    unsigned int t91;
    int t92;
    unsigned int t93;
    unsigned int t94;
    unsigned int t95;
    int t96;
    unsigned int t97;
    unsigned int t98;
    unsigned int t99;
    unsigned int t100;
    char *t102;
    char *t103;
    unsigned int t104;
    unsigned int t105;
    unsigned int t106;
    unsigned int t107;
    unsigned int t108;
    unsigned int t110;
    unsigned int t111;
    unsigned int t112;
    char *t113;
    char *t114;
    char *t115;
    unsigned int t116;
    unsigned int t117;
    unsigned int t118;
    unsigned int t119;
    unsigned int t120;
    unsigned int t121;
    unsigned int t122;
    char *t123;
    char *t124;
    unsigned int t125;
    unsigned int t126;
    unsigned int t127;
    unsigned int t128;
    unsigned int t129;
    unsigned int t130;
    unsigned int t131;
    unsigned int t132;
    int t133;
    int t134;
    unsigned int t135;
    unsigned int t136;
    unsigned int t137;
    unsigned int t138;
    unsigned int t139;
    unsigned int t140;
    char *t141;
    unsigned int t142;
    unsigned int t143;
    unsigned int t144;
    unsigned int t145;
    unsigned int t146;
    char *t147;
    char *t148;

LAB0:    t1 = (t0 + 1712U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(37, ng0);
    t2 = (t0 + 1892);
    *((int *)t2) = 1;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(39, ng0);

LAB5:    xsi_set_current_line(41, ng0);
    t3 = (t0 + 828U);
    t4 = *((char **)t3);
    memset(t5, 0, 8);
    t3 = (t5 + 4U);
    t6 = (t4 + 4U);
    t7 = *((unsigned int *)t6);
    t8 = (~(t7));
    t9 = *((unsigned int *)t4);
    t10 = (t9 & t8);
    t11 = (t10 & 1U);
    if (t11 != 0)
        goto LAB6;

LAB7:    if (*((unsigned int *)t6) != 0)
        goto LAB8;

LAB9:    t12 = (t5 + 4U);
    t13 = *((unsigned int *)t5);
    t14 = *((unsigned int *)t12);
    t15 = (t13 || t14);
    if (t15 > 0)
        goto LAB10;

LAB11:    memcpy(t109, t5, 8);

LAB12:    t141 = (t109 + 4U);
    t142 = *((unsigned int *)t141);
    t143 = (~(t142));
    t144 = *((unsigned int *)t109);
    t145 = (t144 & t143);
    t146 = (t145 != 0);
    if (t146 > 0)
        goto LAB42;

LAB43:    xsi_set_current_line(49, ng0);

LAB46:    xsi_set_current_line(50, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 1052);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(51, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 1144);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(52, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 1236);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);

LAB44:    goto LAB2;

LAB6:    *((unsigned int *)t5) = 1;
    goto LAB9;

LAB8:    *((unsigned int *)t5) = 1;
    *((unsigned int *)t3) = 1;
    goto LAB9;

LAB10:    t16 = (t0 + 740U);
    t17 = *((char **)t16);
    t16 = (t0 + 564U);
    t18 = *((char **)t16);
    memset(t19, 0, 8);
    t16 = (t19 + 4U);
    t20 = (t17 + 4U);
    t21 = (t18 + 4U);
    t22 = *((unsigned int *)t17);
    t23 = *((unsigned int *)t18);
    t24 = (t22 ^ t23);
    t25 = *((unsigned int *)t20);
    t26 = *((unsigned int *)t21);
    t27 = (t25 ^ t26);
    t28 = (t24 | t27);
    t29 = *((unsigned int *)t20);
    t30 = *((unsigned int *)t21);
    t31 = (t29 | t30);
    t32 = (~(t31));
    t33 = (t28 & t32);
    if (t33 != 0)
        goto LAB16;

LAB13:    if (t31 != 0)
        goto LAB15;

LAB14:    *((unsigned int *)t19) = 1;

LAB16:    memset(t34, 0, 8);
    t35 = (t34 + 4U);
    t36 = (t19 + 4U);
    t37 = *((unsigned int *)t36);
    t38 = (~(t37));
    t39 = *((unsigned int *)t19);
    t40 = (t39 & t38);
    t41 = (t40 & 1U);
    if (t41 != 0)
        goto LAB17;

LAB18:    if (*((unsigned int *)t36) != 0)
        goto LAB19;

LAB20:    t42 = (t34 + 4U);
    t43 = *((unsigned int *)t34);
    t44 = (!(t43));
    t45 = *((unsigned int *)t42);
    t46 = (t44 || t45);
    if (t46 > 0)
        goto LAB21;

LAB22:    memcpy(t73, t34, 8);

LAB23:    memset(t101, 0, 8);
    t102 = (t101 + 4U);
    t103 = (t73 + 4U);
    t104 = *((unsigned int *)t103);
    t105 = (~(t104));
    t106 = *((unsigned int *)t73);
    t107 = (t106 & t105);
    t108 = (t107 & 1U);
    if (t108 != 0)
        goto LAB35;

LAB36:    if (*((unsigned int *)t103) != 0)
        goto LAB37;

LAB38:    t110 = *((unsigned int *)t5);
    t111 = *((unsigned int *)t101);
    t112 = (t110 & t111);
    *((unsigned int *)t109) = t112;
    t113 = (t5 + 4U);
    t114 = (t101 + 4U);
    t115 = (t109 + 4U);
    t116 = *((unsigned int *)t113);
    t117 = *((unsigned int *)t114);
    t118 = (t116 | t117);
    *((unsigned int *)t115) = t118;
    t119 = *((unsigned int *)t115);
    t120 = (t119 != 0);
    if (t120 == 1)
        goto LAB39;

LAB40:
LAB41:    goto LAB12;

LAB15:    *((unsigned int *)t19) = 1;
    *((unsigned int *)t16) = 1;
    goto LAB16;

LAB17:    *((unsigned int *)t34) = 1;
    goto LAB20;

LAB19:    *((unsigned int *)t34) = 1;
    *((unsigned int *)t35) = 1;
    goto LAB20;

LAB21:    t47 = (t0 + 740U);
    t48 = *((char **)t47);
    t47 = (t0 + 652U);
    t49 = *((char **)t47);
    memset(t50, 0, 8);
    t47 = (t50 + 4U);
    t51 = (t48 + 4U);
    t52 = (t49 + 4U);
    t53 = *((unsigned int *)t48);
    t54 = *((unsigned int *)t49);
    t55 = (t53 ^ t54);
    t56 = *((unsigned int *)t51);
    t57 = *((unsigned int *)t52);
    t58 = (t56 ^ t57);
    t59 = (t55 | t58);
    t60 = *((unsigned int *)t51);
    t61 = *((unsigned int *)t52);
    t62 = (t60 | t61);
    t63 = (~(t62));
    t64 = (t59 & t63);
    if (t64 != 0)
        goto LAB27;

LAB24:    if (t62 != 0)
        goto LAB26;

LAB25:    *((unsigned int *)t50) = 1;

LAB27:    memset(t65, 0, 8);
    t66 = (t65 + 4U);
    t67 = (t50 + 4U);
    t68 = *((unsigned int *)t67);
    t69 = (~(t68));
    t70 = *((unsigned int *)t50);
    t71 = (t70 & t69);
    t72 = (t71 & 1U);
    if (t72 != 0)
        goto LAB28;

LAB29:    if (*((unsigned int *)t67) != 0)
        goto LAB30;

LAB31:    t74 = *((unsigned int *)t34);
    t75 = *((unsigned int *)t65);
    t76 = (t74 | t75);
    *((unsigned int *)t73) = t76;
    t77 = (t34 + 4U);
    t78 = (t65 + 4U);
    t79 = (t73 + 4U);
    t80 = *((unsigned int *)t77);
    t81 = *((unsigned int *)t78);
    t82 = (t80 | t81);
    *((unsigned int *)t79) = t82;
    t83 = *((unsigned int *)t79);
    t84 = (t83 != 0);
    if (t84 == 1)
        goto LAB32;

LAB33:
LAB34:    goto LAB23;

LAB26:    *((unsigned int *)t50) = 1;
    *((unsigned int *)t47) = 1;
    goto LAB27;

LAB28:    *((unsigned int *)t65) = 1;
    goto LAB31;

LAB30:    *((unsigned int *)t65) = 1;
    *((unsigned int *)t66) = 1;
    goto LAB31;

LAB32:    t85 = *((unsigned int *)t73);
    t86 = *((unsigned int *)t79);
    *((unsigned int *)t73) = (t85 | t86);
    t87 = (t34 + 4U);
    t88 = (t65 + 4U);
    t89 = *((unsigned int *)t87);
    t90 = (~(t89));
    t91 = *((unsigned int *)t34);
    t92 = (t91 & t90);
    t93 = *((unsigned int *)t88);
    t94 = (~(t93));
    t95 = *((unsigned int *)t65);
    t96 = (t95 & t94);
    t97 = (~(t92));
    t98 = (~(t96));
    t99 = *((unsigned int *)t79);
    *((unsigned int *)t79) = (t99 & t97);
    t100 = *((unsigned int *)t79);
    *((unsigned int *)t79) = (t100 & t98);
    goto LAB34;

LAB35:    *((unsigned int *)t101) = 1;
    goto LAB38;

LAB37:    *((unsigned int *)t101) = 1;
    *((unsigned int *)t102) = 1;
    goto LAB38;

LAB39:    t121 = *((unsigned int *)t109);
    t122 = *((unsigned int *)t115);
    *((unsigned int *)t109) = (t121 | t122);
    t123 = (t5 + 4U);
    t124 = (t101 + 4U);
    t125 = *((unsigned int *)t5);
    t126 = (~(t125));
    t127 = *((unsigned int *)t123);
    t128 = (~(t127));
    t129 = *((unsigned int *)t101);
    t130 = (~(t129));
    t131 = *((unsigned int *)t124);
    t132 = (~(t131));
    t133 = (t126 & t128);
    t134 = (t130 & t132);
    t135 = (~(t133));
    t136 = (~(t134));
    t137 = *((unsigned int *)t115);
    *((unsigned int *)t115) = (t137 & t135);
    t138 = *((unsigned int *)t115);
    *((unsigned int *)t115) = (t138 & t136);
    t139 = *((unsigned int *)t109);
    *((unsigned int *)t109) = (t139 & t135);
    t140 = *((unsigned int *)t109);
    *((unsigned int *)t109) = (t140 & t136);
    goto LAB41;

LAB42:    xsi_set_current_line(43, ng0);

LAB45:    xsi_set_current_line(44, ng0);
    t147 = ((char*)((ng1)));
    t148 = (t0 + 1052);
    xsi_vlogvar_assign_value(t148, t147, 0, 0, 1);
    xsi_set_current_line(45, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 1144);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(46, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 1236);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    goto LAB44;

}


extern void work_m_00000000000320752118_3102492762_init()
{
	static char *pe[] = {(void *)A37_0};
	xsi_register_didat("work_m_00000000000320752118_3102492762", "isim/_tmp/work/m_00000000000320752118_3102492762.didat");
	xsi_register_executes(pe);
}
