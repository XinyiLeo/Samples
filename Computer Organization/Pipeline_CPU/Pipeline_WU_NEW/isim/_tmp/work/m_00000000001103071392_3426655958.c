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
static const char *ng0 = "C:/Users/wuxy3/Desktop/Pipeline_WU_NEW/IF_STAGE.v";
static int ng1[] = {0, 0};
static int ng2[] = {64, 0};
static unsigned int ng3[] = {0U, 0U};
static int ng4[] = {1, 0};
static unsigned int ng5[] = {537395232U, 0U};
static unsigned int ng6[] = {537460791U, 0U};
static unsigned int ng7[] = {17399840U, 0U};
static int ng8[] = {2, 0};
static unsigned int ng9[] = {17401890U, 0U};
static int ng10[] = {3, 0};
static unsigned int ng11[] = {17403940U, 0U};
static int ng12[] = {4, 0};
static unsigned int ng13[] = {17405989U, 0U};
static int ng14[] = {5, 0};
static unsigned int ng15[] = {17408042U, 0U};
static int ng16[] = {6, 0};
static unsigned int ng17[] = {310378502U, 0U};
static int ng18[] = {7, 0};
static unsigned int ng19[] = {17387552U, 0U};
static int ng20[] = {8, 0};
static unsigned int ng21[] = {21581856U, 0U};
static int ng22[] = {9, 0};
static unsigned int ng23[] = {21518368U, 0U};
static int ng24[] = {10, 0};
static unsigned int ng25[] = {2350186500U, 0U};
static int ng26[] = {11, 0};
static unsigned int ng27[] = {22392864U, 0U};
static int ng28[] = {12, 0};
static unsigned int ng29[] = {44808224U, 0U};
static int ng30[] = {13, 0};
static unsigned int ng31[] = {2887057416U, 0U};
static int ng32[] = {14, 0};
static unsigned int ng33[] = {134217734U, 0U};
static int ng34[] = {15, 0};



static void I40_0(char *t0)
{
    char t5[8];
    char t14[8];
    char t15[8];
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
    char *t13;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    unsigned int t26;
    int t27;
    char *t28;
    unsigned int t29;
    int t30;
    int t31;
    unsigned int t32;
    unsigned int t33;
    int t34;
    int t35;

LAB0:    xsi_set_current_line(40, ng0);

LAB2:    xsi_set_current_line(42, ng0);
    xsi_set_current_line(42, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 1316);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);

LAB3:    t1 = (t0 + 1316);
    t2 = (t1 + 32U);
    t3 = *((char **)t2);
    t4 = ((char*)((ng2)));
    memset(t5, 0, 8);
    xsi_vlog_signed_less(t5, 32, t3, 32, t4, 32);
    t6 = (t5 + 4U);
    t7 = *((unsigned int *)t6);
    t8 = (~(t7));
    t9 = *((unsigned int *)t5);
    t10 = (t9 & t8);
    t11 = (t10 != 0);
    if (t11 > 0)
        goto LAB4;

LAB5:    xsi_set_current_line(46, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 1500);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);
    xsi_set_current_line(49, ng0);
    t1 = ((char*)((ng5)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng1)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB9;

LAB10:    xsi_set_current_line(50, ng0);
    t1 = ((char*)((ng6)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng4)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB11;

LAB12:    xsi_set_current_line(51, ng0);
    t1 = ((char*)((ng7)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng8)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB13;

LAB14:    xsi_set_current_line(52, ng0);
    t1 = ((char*)((ng9)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng10)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB15;

LAB16:    xsi_set_current_line(53, ng0);
    t1 = ((char*)((ng11)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng12)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB17;

LAB18:    xsi_set_current_line(54, ng0);
    t1 = ((char*)((ng13)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng14)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB19;

LAB20:    xsi_set_current_line(55, ng0);
    t1 = ((char*)((ng15)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng16)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB21;

LAB22:    xsi_set_current_line(56, ng0);
    t1 = ((char*)((ng17)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng18)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB23;

LAB24:    xsi_set_current_line(57, ng0);
    t1 = ((char*)((ng19)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng20)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB25;

LAB26:    xsi_set_current_line(58, ng0);
    t1 = ((char*)((ng21)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng22)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB27;

LAB28:    xsi_set_current_line(59, ng0);
    t1 = ((char*)((ng23)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng24)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB29;

LAB30:    xsi_set_current_line(60, ng0);
    t1 = ((char*)((ng25)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng26)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB31;

LAB32:    xsi_set_current_line(61, ng0);
    t1 = ((char*)((ng27)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng28)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB33;

LAB34:    xsi_set_current_line(62, ng0);
    t1 = ((char*)((ng29)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng30)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB35;

LAB36:    xsi_set_current_line(63, ng0);
    t1 = ((char*)((ng31)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng32)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB37;

LAB38:    xsi_set_current_line(64, ng0);
    t1 = ((char*)((ng33)));
    t2 = (t0 + 1408);
    t3 = (t0 + 1408);
    t4 = (t3 + 40U);
    t6 = *((char **)t4);
    t12 = (t0 + 1408);
    t13 = (t12 + 36U);
    t16 = *((char **)t13);
    t17 = ((char*)((ng34)));
    xsi_vlog_generic_convert_array_indices(t5, t14, t6, t16, 2, 1, t17, 32, 1);
    t18 = (t5 + 4U);
    t7 = *((unsigned int *)t18);
    t27 = (!(t7));
    t19 = (t14 + 4U);
    t8 = *((unsigned int *)t19);
    t30 = (!(t8));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB39;

LAB40:
LAB1:    return;
LAB4:    xsi_set_current_line(43, ng0);

LAB6:    xsi_set_current_line(44, ng0);
    t12 = ((char*)((ng3)));
    t13 = (t0 + 1408);
    t16 = (t0 + 1408);
    t17 = (t16 + 40U);
    t18 = *((char **)t17);
    t19 = (t0 + 1408);
    t20 = (t19 + 36U);
    t21 = *((char **)t20);
    t22 = (t0 + 1316);
    t23 = (t22 + 32U);
    t24 = *((char **)t23);
    xsi_vlog_generic_convert_array_indices(t14, t15, t18, t21, 2, 1, t24, 32, 1);
    t25 = (t14 + 4U);
    t26 = *((unsigned int *)t25);
    t27 = (!(t26));
    t28 = (t15 + 4U);
    t29 = *((unsigned int *)t28);
    t30 = (!(t29));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB7;

LAB8:    xsi_set_current_line(42, ng0);
    t1 = (t0 + 1316);
    t2 = (t1 + 32U);
    t3 = *((char **)t2);
    t4 = ((char*)((ng4)));
    memset(t5, 0, 8);
    xsi_vlog_signed_add(t5, 32, t3, 32, t4, 32);
    t6 = (t0 + 1316);
    xsi_vlogvar_assign_value(t6, t5, 0, 0, 32);
    goto LAB3;

LAB7:    t32 = *((unsigned int *)t14);
    t33 = *((unsigned int *)t15);
    t34 = (t32 - t33);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t13, t12, 0, *((unsigned int *)t15), t35);
    goto LAB8;

LAB9:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB10;

LAB11:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB12;

LAB13:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB14;

LAB15:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB16;

LAB17:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB18;

LAB19:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB20;

LAB21:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB22;

LAB23:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB24;

LAB25:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB26;

LAB27:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB28;

LAB29:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB30;

LAB31:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB32;

LAB33:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB34;

LAB35:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB36;

LAB37:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB38;

LAB39:    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t14);
    t34 = (t9 - t10);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t14), t35);
    goto LAB40;

}

static void C67_1(char *t0)
{
    char t6[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;

LAB0:    t1 = (t0 + 2104U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 1500);
    t3 = (t2 + 32U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng12)));
    memset(t6, 0, 8);
    xsi_vlog_unsigned_add(t6, 32, t4, 32, t5, 32);
    t7 = (t0 + 2600);
    t8 = (t7 + 32U);
    t9 = *((char **)t8);
    t10 = (t9 + 40U);
    t11 = *((char **)t10);
    memcpy(t11, t6, 8);
    xsi_driver_vfirst_trans(t7, 0, 31);
    t12 = (t0 + 2540);
    *((int *)t12) = 1;

LAB1:    return;
}

static void C68_2(char *t0)
{
    char t5[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    unsigned int t21;
    unsigned int t22;
    char *t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    char *t30;

LAB0:    t1 = (t0 + 2232U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 1408);
    t3 = (t2 + 32U);
    t4 = *((char **)t3);
    t6 = (t0 + 1408);
    t7 = (t6 + 40U);
    t8 = *((char **)t7);
    t9 = (t0 + 1408);
    t10 = (t9 + 36U);
    t11 = *((char **)t10);
    t12 = (t0 + 1500);
    t13 = (t12 + 32U);
    t14 = *((char **)t13);
    xsi_vlog_generic_get_array_select_value(t5, 32, t4, t8, t11, 2, 1, t14, 32, 2);
    t15 = (t0 + 2636);
    t16 = (t15 + 32U);
    t17 = *((char **)t16);
    t18 = (t17 + 40U);
    t19 = *((char **)t18);
    t20 = (t19 + 4U);
    t21 = 1U;
    t22 = t21;
    t23 = (t5 + 4U);
    t24 = *((unsigned int *)t5);
    t21 = (t21 & t24);
    t25 = *((unsigned int *)t23);
    t22 = (t22 & t25);
    t26 = *((unsigned int *)t19);
    *((unsigned int *)t19) = (t26 & 4294967294U);
    t27 = *((unsigned int *)t19);
    *((unsigned int *)t19) = (t27 | t21);
    t28 = *((unsigned int *)t20);
    *((unsigned int *)t20) = (t28 & 4294967294U);
    t29 = *((unsigned int *)t20);
    *((unsigned int *)t20) = (t29 | t22);
    xsi_driver_vfirst_trans(t15, 0, 0);
    t30 = (t0 + 2548);
    *((int *)t30) = 1;

LAB1:    return;
}

static void A71_3(char *t0)
{
    char t5[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t6;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    char *t27;
    char *t28;
    int t29;

LAB0:    t1 = (t0 + 2360U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(71, ng0);
    t2 = (t0 + 2556);
    *((int *)t2) = 1;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(72, ng0);

LAB5:    xsi_set_current_line(74, ng0);
    t3 = (t0 + 828U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng4)));
    memset(t5, 0, 8);
    t6 = (t5 + 4U);
    t7 = (t4 + 4U);
    t8 = (t3 + 4U);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t3);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB9;

LAB6:    if (t18 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t5) = 1;

LAB9:    t21 = (t5 + 4U);
    t22 = *((unsigned int *)t21);
    t23 = (~(t22));
    t24 = *((unsigned int *)t5);
    t25 = (t24 & t23);
    t26 = (t25 != 0);
    if (t26 > 0)
        goto LAB10;

LAB11:    xsi_set_current_line(75, ng0);

LAB13:    xsi_set_current_line(76, ng0);
    t2 = (t0 + 652U);
    t3 = *((char **)t2);

LAB14:    t2 = ((char*)((ng1)));
    t29 = xsi_vlog_unsigned_case_compare(t3, 1, t2, 32);
    if (t29 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng4)));
    t29 = xsi_vlog_unsigned_case_compare(t3, 1, t2, 32);
    if (t29 == 1)
        goto LAB17;

LAB18:
LAB19:
LAB12:    goto LAB2;

LAB8:    *((unsigned int *)t5) = 1;
    *((unsigned int *)t6) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(74, ng0);
    t27 = ((char*)((ng1)));
    t28 = (t0 + 1500);
    xsi_vlogvar_assign_value(t28, t27, 0, 0, 32);
    goto LAB12;

LAB15:    xsi_set_current_line(77, ng0);
    t4 = (t0 + 1500);
    t6 = (t4 + 32U);
    t7 = *((char **)t6);
    t8 = ((char*)((ng12)));
    memset(t5, 0, 8);
    xsi_vlog_unsigned_add(t5, 32, t7, 32, t8, 32);
    t21 = (t0 + 1500);
    xsi_vlogvar_assign_value(t21, t5, 0, 0, 32);
    goto LAB19;

LAB17:    xsi_set_current_line(78, ng0);
    t4 = (t0 + 564U);
    t6 = *((char **)t4);
    t4 = (t0 + 1500);
    xsi_vlogvar_assign_value(t4, t6, 0, 0, 32);
    goto LAB19;

}


extern void work_m_00000000001103071392_3426655958_init()
{
	static char *pe[] = {(void *)I40_0,(void *)C67_1,(void *)C68_2,(void *)A71_3};
	xsi_register_didat("work_m_00000000001103071392_3426655958", "isim/_tmp/work/m_00000000001103071392_3426655958.didat");
	xsi_register_executes(pe);
}
