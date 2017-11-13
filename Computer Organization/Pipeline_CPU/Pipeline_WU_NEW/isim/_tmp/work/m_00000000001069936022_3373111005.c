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
static const char *ng0 = "";
static const char *ng1 = " ";
static const char *ng2 = "clock = %d Address_out = %d ReadData_MEM = %d";
static const char *ng3 = "C:/Users/wuxy3/Desktop/Pipeline_WU_NEW/MEM_STAGE.v";
static const char *ng4 = "The debug process in ID_STAGE";
static int ng5[] = {0, 0};
static int ng6[] = {64, 0};
static unsigned int ng7[] = {0U, 0U};
static int ng8[] = {1, 0};
static int ng9[] = {4, 0};

void M48_6(char *);
void M48_6(char *);


static void M48_6_Func(char *t0)
{
    char t1[16];
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;

LAB0:    t2 = xsi_vlog_time(t1, 1000000.000000000, 1000.000000000000);
    xsi_vlogfile_write(0, 0, ng0, 2, t0, (char)118, t1, 64);
    xsi_vlogfile_write(0, 0, ng1, 1, t0);
    t3 = (t0 + 1180U);
    t4 = *((char **)t3);
    t3 = (t0 + 1884U);
    t5 = *((char **)t3);
    t3 = (t0 + 2376);
    t6 = (t3 + 32U);
    t7 = *((char **)t6);
    xsi_vlogfile_write(1, 0, ng2, 4, t0, (char)118, t4, 1, (char)118, t5, 32, (char)118, t7, 32);

LAB1:    return;
}

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

LAB0:    t1 = (t0 + 2944U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 828U);
    t3 = *((char **)t2);
    t2 = (t0 + 4240);
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
    t18 = (t0 + 4148);
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

LAB0:    t1 = (t0 + 3072U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 916U);
    t3 = *((char **)t2);
    t2 = (t0 + 4276);
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
    t18 = (t0 + 4156);
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

LAB0:    t1 = (t0 + 3200U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 1444U);
    t3 = *((char **)t2);
    t2 = (t0 + 4312);
    t4 = (t2 + 32U);
    t5 = *((char **)t4);
    t6 = (t5 + 40U);
    t7 = *((char **)t6);
    memcpy(t7, t3, 8);
    xsi_driver_vfirst_trans(t2, 0, 31);
    t8 = (t0 + 4164);
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

LAB0:    t1 = (t0 + 3328U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 1620U);
    t3 = *((char **)t2);
    t2 = (t0 + 4348);
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
    t18 = (t0 + 4172);
    *((int *)t18) = 1;

LAB1:    return;
}

static void G44_4(char *t0)
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

LAB0:    t1 = (t0 + 3456U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 652U);
    t3 = *((char **)t2);
    t2 = (t0 + 740U);
    t4 = *((char **)t2);
    t2 = (t0 + 4384);
    t5 = (t2 + 32U);
    t6 = *((char **)t5);
    t7 = (t6 + 40U);
    t8 = *((char **)t7);
    xsi_vlog_AndGate(t8, 2U, t3, t4);
    t9 = (t0 + 4384);
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
    t24 = (t0 + 4384);
    xsi_driver_vfirst_trans(t24, 0, 0);
    t25 = (t0 + 4180);
    *((int *)t25) = 1;

LAB1:    return;
}

static void I46_5(char *t0)
{

LAB0:    xsi_set_current_line(46, ng3);

LAB2:    xsi_set_current_line(47, ng3);
    xsi_vlogfile_write(1, 0, ng4, 1, t0);
    xsi_set_current_line(48, ng3);
    M48_6(t0);

LAB1:    return;
}

static void I50_7(char *t0)
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

LAB0:    xsi_set_current_line(50, ng3);

LAB2:    xsi_set_current_line(51, ng3);
    xsi_set_current_line(51, ng3);
    t1 = ((char*)((ng5)));
    t2 = (t0 + 2284);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);

LAB3:    t1 = (t0 + 2284);
    t2 = (t1 + 32U);
    t3 = *((char **)t2);
    t4 = ((char*)((ng6)));
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
LAB4:    xsi_set_current_line(52, ng3);

LAB6:    xsi_set_current_line(53, ng3);
    t12 = ((char*)((ng7)));
    t13 = (t0 + 2468);
    t16 = (t0 + 2468);
    t17 = (t16 + 40U);
    t18 = *((char **)t17);
    t19 = (t0 + 2468);
    t20 = (t19 + 36U);
    t21 = *((char **)t20);
    t22 = (t0 + 2284);
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

LAB8:    xsi_set_current_line(51, ng3);
    t1 = (t0 + 2284);
    t2 = (t1 + 32U);
    t3 = *((char **)t2);
    t4 = ((char*)((ng8)));
    memset(t5, 0, 8);
    xsi_vlog_signed_add(t5, 32, t3, 32, t4, 32);
    t6 = (t0 + 2284);
    xsi_vlogvar_assign_value(t6, t5, 0, 0, 32);
    goto LAB3;

LAB7:    t32 = *((unsigned int *)t14);
    t33 = *((unsigned int *)t15);
    t34 = (t32 - t33);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t13, t12, 0, *((unsigned int *)t15), t35);
    goto LAB8;

}

static void A57_8(char *t0)
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

LAB0:    t1 = (t0 + 3840U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(57, ng3);
    t2 = (t0 + 4188);
    *((int *)t2) = 1;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(57, ng3);

LAB5:    xsi_set_current_line(58, ng3);
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

LAB7:    xsi_set_current_line(59, ng3);
    t2 = (t0 + 1004U);
    t3 = *((char **)t2);
    t2 = (t3 + 4U);
    t5 = *((unsigned int *)t2);
    t6 = (~(t5));
    t7 = *((unsigned int *)t3);
    t8 = (t7 & t6);
    t9 = (t8 != 0);
    if (t9 > 0)
        goto LAB11;

LAB12:
LAB13:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(58, ng3);
    t10 = (t0 + 1532U);
    t11 = *((char **)t10);
    t10 = (t0 + 2468);
    t14 = (t0 + 2468);
    t15 = (t14 + 40U);
    t16 = *((char **)t15);
    t17 = (t0 + 2468);
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
    t30 = ((char*)((ng9)));
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

LAB11:    xsi_set_current_line(59, ng3);
    t4 = (t0 + 2468);
    t10 = (t4 + 32U);
    t11 = *((char **)t10);
    t14 = (t0 + 2468);
    t15 = (t14 + 40U);
    t16 = *((char **)t15);
    t17 = (t0 + 2468);
    t18 = (t17 + 36U);
    t19 = *((char **)t18);
    t21 = (t0 + 1444U);
    t22 = *((char **)t21);
    memset(t13, 0, 8);
    t21 = (t13 + 4U);
    t23 = (t22 + 4U);
    t24 = *((unsigned int *)t22);
    t25 = (t24 >> 0);
    *((unsigned int *)t13) = t25;
    t26 = *((unsigned int *)t23);
    t27 = (t26 >> 0);
    *((unsigned int *)t21) = t27;
    t28 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t28 & 255U);
    t29 = *((unsigned int *)t21);
    *((unsigned int *)t21) = (t29 & 255U);
    t30 = ((char*)((ng9)));
    memset(t20, 0, 8);
    xsi_vlog_unsigned_divide(t20, 32, t13, 32, t30, 32);
    xsi_vlog_generic_get_array_select_value(t12, 32, t11, t16, t19, 2, 1, t20, 32, 2);
    t32 = (t0 + 2376);
    xsi_vlogvar_assign_value(t32, t12, 0, 0, 32);
    goto LAB13;

}

void M48_6(char *t0)
{
    char *t1;
    char *t2;

LAB0:    t1 = (t0 + 3884);
    t2 = (t0 + 4196);
    xsi_vlogfile_monitor((void *)M48_6_Func, t1, t2);

LAB1:    return;
}


extern void work_m_00000000001069936022_3373111005_init()
{
	static char *pe[] = {(void *)C39_0,(void *)C40_1,(void *)C41_2,(void *)C42_3,(void *)G44_4,(void *)I46_5,(void *)I50_7,(void *)A57_8,(void *)M48_6};
	xsi_register_didat("work_m_00000000001069936022_3373111005", "isim/_tmp/work/m_00000000001069936022_3373111005.didat");
	xsi_register_executes(pe);
}
