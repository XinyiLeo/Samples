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
static const char *ng0 = "C:/Users/wuxy3/Desktop/Pipeline_WU_NEW/MEM_STAGE.v";
static int ng1[] = {0, 0};
static int ng2[] = {64, 0};
static unsigned int ng3[] = {0U, 0U};
static int ng4[] = {1, 0};
static int ng5[] = {4, 0};
static unsigned int ng6[] = {4294967295U, 4294967295U};



static void C39_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 2940U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 828U);
    t3 = *((char **)t2);
    t2 = (t0 + 4108);
    t4 = (t2 + 32U);
    t5 = *((char **)t4);
    t6 = (t5 + 40U);
    t7 = *((char **)t6);
    t8 = (t7 + 4U);
    t9 = 1U;
    t10 = t9;
    t11 = (t3 + 4U);
    t12 = *((unsigned int *)t3);
    t9 = (t9 & t12);
    t13 = *((unsigned int *)t11);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t14 & 4294967294U);
    t15 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t15 | t9);
    t16 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t16 & 4294967294U);
    t17 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t17 | t10);
    xsi_driver_vfirst_trans(t2, 0, 0);
    t18 = (t0 + 4016);
    *((int *)t18) = 1;

LAB1:    return;
}

static void C40_1(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 3068U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 916U);
    t3 = *((char **)t2);
    t2 = (t0 + 4144);
    t4 = (t2 + 32U);
    t5 = *((char **)t4);
    t6 = (t5 + 40U);
    t7 = *((char **)t6);
    t8 = (t7 + 4U);
    t9 = 1U;
    t10 = t9;
    t11 = (t3 + 4U);
    t12 = *((unsigned int *)t3);
    t9 = (t9 & t12);
    t13 = *((unsigned int *)t11);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t14 & 4294967294U);
    t15 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t15 | t9);
    t16 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t16 & 4294967294U);
    t17 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t17 | t10);
    xsi_driver_vfirst_trans(t2, 0, 0);
    t18 = (t0 + 4024);
    *((int *)t18) = 1;

LAB1:    return;
}

static void C41_2(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;

LAB0:    t1 = (t0 + 3196U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 1444U);
    t3 = *((char **)t2);
    t2 = (t0 + 4180);
    t4 = (t2 + 32U);
    t5 = *((char **)t4);
    t6 = (t5 + 40U);
    t7 = *((char **)t6);
    memcpy(t7, t3, 8);
    xsi_driver_vfirst_trans(t2, 0, 31);
    t8 = (t0 + 4032);
    *((int *)t8) = 1;

LAB1:    return;
}

static void C42_3(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 3324U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 1620U);
    t3 = *((char **)t2);
    t2 = (t0 + 4216);
    t4 = (t2 + 32U);
    t5 = *((char **)t4);
    t6 = (t5 + 40U);
    t7 = *((char **)t6);
    t8 = (t7 + 4U);
    t9 = 31U;
    t10 = t9;
    t11 = (t3 + 4U);
    t12 = *((unsigned int *)t3);
    t9 = (t9 & t12);
    t13 = *((unsigned int *)t11);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t14 & 4294967264U);
    t15 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t15 | t9);
    t16 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t16 & 4294967264U);
    t17 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t17 | t10);
    xsi_driver_vfirst_trans(t2, 0, 4);
    t18 = (t0 + 4040);
    *((int *)t18) = 1;

LAB1:    return;
}

static void G43_4(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    unsigned int t15;
    unsigned int t16;
    char *t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    char *t24;
    char *t25;

LAB0:    t1 = (t0 + 3452U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 652U);
    t3 = *((char **)t2);
    t2 = (t0 + 740U);
    t4 = *((char **)t2);
    t2 = (t0 + 4252);
    t5 = (t2 + 32U);
    t6 = *((char **)t5);
    t7 = (t6 + 40U);
    t8 = *((char **)t7);
    xsi_vlog_AndGate(t8, 2U, t3, t4);
    t9 = (t0 + 4252);
    t10 = (t9 + 32U);
    t11 = *((char **)t10);
    t12 = (t11 + 40U);
    t13 = *((char **)t12);
    t14 = (t13 + 4U);
    t15 = 1U;
    t16 = t15;
    t17 = (t8 + 4U);
    t18 = *((unsigned int *)t8);
    t15 = (t15 & t18);
    t19 = *((unsigned int *)t17);
    t16 = (t16 & t19);
    t20 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t20 & 4294967294U);
    t21 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t21 | t15);
    t22 = *((unsigned int *)t14);
    *((unsigned int *)t14) = (t22 & 4294967294U);
    t23 = *((unsigned int *)t14);
    *((unsigned int *)t14) = (t23 | t16);
    t24 = (t0 + 4252);
    xsi_driver_vfirst_trans(t24, 0, 0);
    t25 = (t0 + 4048);
    *((int *)t25) = 1;

LAB1:    return;
}

static void I54_5(char *t0)
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

LAB0:    xsi_set_current_line(54, ng0);

LAB2:    xsi_set_current_line(55, ng0);
    xsi_set_current_line(55, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 2372);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);

LAB3:    t1 = (t0 + 2372);
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

LAB5:
LAB1:    return;
LAB4:    xsi_set_current_line(56, ng0);

LAB6:    xsi_set_current_line(57, ng0);
    t12 = ((char*)((ng3)));
    t13 = (t0 + 2464);
    t16 = (t0 + 2464);
    t17 = (t16 + 40U);
    t18 = *((char **)t17);
    t19 = (t0 + 2464);
    t20 = (t19 + 36U);
    t21 = *((char **)t20);
    t22 = (t0 + 2372);
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

LAB8:    xsi_set_current_line(55, ng0);
    t1 = (t0 + 2372);
    t2 = (t1 + 32U);
    t3 = *((char **)t2);
    t4 = ((char*)((ng4)));
    memset(t5, 0, 8);
    xsi_vlog_signed_add(t5, 32, t3, 32, t4, 32);
    t6 = (t0 + 2372);
    xsi_vlogvar_assign_value(t6, t5, 0, 0, 32);
    goto LAB3;

LAB7:    t32 = *((unsigned int *)t14);
    t33 = *((unsigned int *)t15);
    t34 = (t32 - t33);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t13, t12, 0, *((unsigned int *)t15), t35);
    goto LAB8;

}

static void C61_6(char *t0)
{
    char t3[8];
    char t4[8];
    char t19[8];
    char t26[8];
    char t37[8];
    char *t1;
    char *t2;
    char *t5;
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
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t27;
    char *t28;
    char *t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    char *t36;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    char *t42;
    char *t43;
    char *t44;
    char *t45;
    char *t46;
    char *t47;
    char *t48;

LAB0:    t1 = (t0 + 3708U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 1004U);
    t5 = *((char **)t2);
    memset(t4, 0, 8);
    t2 = (t4 + 4U);
    t6 = (t5 + 4U);
    t7 = *((unsigned int *)t6);
    t8 = (~(t7));
    t9 = *((unsigned int *)t5);
    t10 = (t9 & t8);
    t11 = (t10 & 1U);
    if (t11 != 0)
        goto LAB4;

LAB5:    if (*((unsigned int *)t6) != 0)
        goto LAB6;

LAB7:    t12 = (t4 + 4U);
    t13 = *((unsigned int *)t4);
    t14 = *((unsigned int *)t12);
    t15 = (t13 || t14);
    if (t15 > 0)
        goto LAB8;

LAB9:    t38 = *((unsigned int *)t4);
    t39 = (~(t38));
    t40 = *((unsigned int *)t12);
    t41 = (t39 || t40);
    if (t41 > 0)
        goto LAB10;

LAB11:    if (*((unsigned int *)t12) > 0)
        goto LAB12;

LAB13:    if (*((unsigned int *)t4) > 0)
        goto LAB14;

LAB15:    memcpy(t3, t42, 8);

LAB16:    t43 = (t0 + 4288);
    t44 = (t43 + 32U);
    t45 = *((char **)t44);
    t46 = (t45 + 40U);
    t47 = *((char **)t46);
    memcpy(t47, t3, 8);
    xsi_driver_vfirst_trans(t43, 0, 31);
    t48 = (t0 + 4056);
    *((int *)t48) = 1;

LAB1:    return;
LAB4:    *((unsigned int *)t4) = 1;
    goto LAB7;

LAB6:    *((unsigned int *)t4) = 1;
    *((unsigned int *)t2) = 1;
    goto LAB7;

LAB8:    t16 = (t0 + 2464);
    t17 = (t16 + 32U);
    t18 = *((char **)t17);
    t20 = (t0 + 2464);
    t21 = (t20 + 40U);
    t22 = *((char **)t21);
    t23 = (t0 + 2464);
    t24 = (t23 + 36U);
    t25 = *((char **)t24);
    t27 = (t0 + 1444U);
    t28 = *((char **)t27);
    memset(t26, 0, 8);
    t27 = (t26 + 4U);
    t29 = (t28 + 4U);
    t30 = *((unsigned int *)t28);
    t31 = (t30 >> 0);
    *((unsigned int *)t26) = t31;
    t32 = *((unsigned int *)t29);
    t33 = (t32 >> 0);
    *((unsigned int *)t27) = t33;
    t34 = *((unsigned int *)t26);
    *((unsigned int *)t26) = (t34 & 255U);
    t35 = *((unsigned int *)t27);
    *((unsigned int *)t27) = (t35 & 255U);
    t36 = ((char*)((ng5)));
    memset(t37, 0, 8);
    xsi_vlog_unsigned_divide(t37, 32, t26, 32, t36, 32);
    xsi_vlog_generic_get_array_select_value(t19, 32, t18, t22, t25, 2, 1, t37, 32, 2);
    goto LAB9;

LAB10:    t42 = ((char*)((ng6)));
    goto LAB11;

LAB12:    xsi_vlog_unsigned_bit_combine(t3, 32, t19, 32, t42, 32);
    goto LAB16;

LAB14:    memcpy(t3, t19, 8);
    goto LAB16;

}

static void A63_7(char *t0)
{
    char t12[8];
    char t13[8];
    char t20[8];
    char t31[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    unsigned int t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    char *t10;
    char *t11;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t21;
    char *t22;
    char *t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    char *t30;
    char *t32;
    unsigned int t33;
    int t34;
    char *t35;
    unsigned int t36;
    int t37;
    int t38;
    unsigned int t39;
    unsigned int t40;
    int t41;
    int t42;

LAB0:    t1 = (t0 + 3836U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(63, ng0);
    t2 = (t0 + 4064);
    *((int *)t2) = 1;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(63, ng0);

LAB5:    xsi_set_current_line(64, ng0);
    t3 = (t0 + 564U);
    t4 = *((char **)t3);
    t3 = (t4 + 4U);
    t5 = *((unsigned int *)t3);
    t6 = (~(t5));
    t7 = *((unsigned int *)t4);
    t8 = (t7 & t6);
    t9 = (t8 != 0);
    if (t9 > 0)
        goto LAB6;

LAB7:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(64, ng0);
    t10 = (t0 + 1532U);
    t11 = *((char **)t10);
    t10 = (t0 + 2464);
    t14 = (t0 + 2464);
    t15 = (t14 + 40U);
    t16 = *((char **)t15);
    t17 = (t0 + 2464);
    t18 = (t17 + 36U);
    t19 = *((char **)t18);
    t21 = (t0 + 1444U);
    t22 = *((char **)t21);
    memset(t20, 0, 8);
    t21 = (t20 + 4U);
    t23 = (t22 + 4U);
    t24 = *((unsigned int *)t22);
    t25 = (t24 >> 0);
    *((unsigned int *)t20) = t25;
    t26 = *((unsigned int *)t23);
    t27 = (t26 >> 0);
    *((unsigned int *)t21) = t27;
    t28 = *((unsigned int *)t20);
    *((unsigned int *)t20) = (t28 & 255U);
    t29 = *((unsigned int *)t21);
    *((unsigned int *)t21) = (t29 & 255U);
    t30 = ((char*)((ng5)));
    memset(t31, 0, 8);
    xsi_vlog_unsigned_divide(t31, 32, t20, 32, t30, 32);
    xsi_vlog_generic_convert_array_indices(t12, t13, t16, t19, 2, 1, t31, 32, 2);
    t32 = (t12 + 4U);
    t33 = *((unsigned int *)t32);
    t34 = (!(t33));
    t35 = (t13 + 4U);
    t36 = *((unsigned int *)t35);
    t37 = (!(t36));
    t38 = (t34 && t37);
    if (t38 == 1)
        goto LAB9;

LAB10:    goto LAB8;

LAB9:    t39 = *((unsigned int *)t12);
    t40 = *((unsigned int *)t13);
    t41 = (t39 - t40);
    t42 = (t41 + 1);
    xsi_vlogvar_assign_value(t10, t11, 0, *((unsigned int *)t13), t42);
    goto LAB10;

}


extern void work_m_00000000003395629240_3373111005_init()
{
	static char *pe[] = {(void *)C39_0,(void *)C40_1,(void *)C41_2,(void *)C42_3,(void *)G43_4,(void *)I54_5,(void *)C61_6,(void *)A63_7};
	xsi_register_didat("work_m_00000000003395629240_3373111005", "isim/_tmp/work/m_00000000003395629240_3373111005.didat");
	xsi_register_executes(pe);
}
