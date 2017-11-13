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
static const char *ng2 = "clock = %d, Address = %h PCSrc = %h";
static int ng3[] = {4, 0};
static const char *ng4 = "C:/Users/wuxy3/Desktop/Pipeline_WU_NEW/Main.v";
static const char *ng5 = "The debug process in main block";

void M107_2(char *);
void M107_2(char *);


static void M107_2_Func(char *t0)
{
    char t1[16];
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;

LAB0:    t2 = xsi_vlog_time(t1, 1000000.000000000, 1000.000000000000);
    xsi_vlogfile_write(0, 0, ng0, 2, t0, (char)118, t1, 64);
    xsi_vlogfile_write(0, 0, ng1, 1, t0);
    t3 = (t0 + 652U);
    t4 = *((char **)t3);
    t3 = (t0 + 740U);
    t5 = *((char **)t3);
    t3 = (t0 + 916U);
    t6 = *((char **)t3);
    xsi_vlogfile_write(1, 0, ng2, 4, t0, (char)118, t4, 1, (char)118, t5, 32, (char)118, t6, 1);

LAB1:    return;
}

static void C90_0(char *t0)
{
    char t4[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;

LAB0:    t1 = (t0 + 7772U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 1092U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng3)));
    memset(t4, 0, 8);
    xsi_vlog_unsigned_minus(t4, 32, t3, 32, t2, 32);
    t5 = (t0 + 8260);
    t6 = (t5 + 32U);
    t7 = *((char **)t6);
    t8 = (t7 + 40U);
    t9 = *((char **)t8);
    memcpy(t9, t4, 8);
    xsi_driver_vfirst_trans(t5, 0, 31);
    t10 = (t0 + 8208);
    *((int *)t10) = 1;

LAB1:    return;
}

static void I105_1(char *t0)
{

LAB0:    xsi_set_current_line(105, ng4);

LAB2:    xsi_set_current_line(106, ng4);
    xsi_vlogfile_write(1, 0, ng5, 1, t0);
    xsi_set_current_line(107, ng4);
    M107_2(t0);

LAB1:    return;
}

void M107_2(char *t0)
{
    char *t1;
    char *t2;

LAB0:    t1 = (t0 + 7944);
    t2 = (t0 + 8216);
    xsi_vlogfile_monitor((void *)M107_2_Func, t1, t2);

LAB1:    return;
}


extern void work_m_00000000000970558611_2973510161_init()
{
	static char *pe[] = {(void *)C90_0,(void *)I105_1,(void *)M107_2};
	xsi_register_didat("work_m_00000000000970558611_2973510161", "isim/_tmp/work/m_00000000000970558611_2973510161.didat");
	xsi_register_executes(pe);
}
