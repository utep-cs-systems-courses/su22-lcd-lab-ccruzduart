#ifndef buzzer_included
#define buzzer_included

void buzzer_init();
void buzzer_set_period(short cycles);

#define tuned 2000000

#define C_3 (tuned/132.60)
#define C_s3 (tuned/140.28)
#define D_3 (tuned/148.83)
#define E_3 (tuned/167.06)
#define F_3 (tuned/177.00)
#define F_s3 (tuned/187.52)
#define G_3 (tuned/198.67)
#define G_s3 (tuned/210.48)
#define A_3 (tuned/223.00)
#define A_s3 (tuned/236.26)
#define B_3 (tuned/250.31)
#define C_4 (tuned/265.19)
#define C_s4 (tuned/280.96)
#define D_4 (tuned/297.67)
#define D_s4 (tuned/315.37)
#define E_4 (tuned/334.12)
#define F_4 (tuned/353.99)
#define F_s4 (tuned/353.99)
#define G_4 (tuned/397.34)
#define G_s4 (tuned/420.97)
#define A_4 (tuned/446)
#define B_4 (tuned/500.62)
#define C_5 (tuned/530.39)
#define C_s5 (tuned/530.39)
#define D_5 (tuned/595.34)
#define D_s5 (tuned/630.74)
#define E_5 (tuned/668.24)
#define F_5 (tuned/707.98)
#define F_s5 (tuned/750.08)
#define G_5 (tuned/794.68)
#define G_s5 (tuned/841.94)
#define A_5 (tuned/892)
#define A_s5 (tuned/945.04)
#define B_5 (tuned/1001.24)
#define C_6 (tuned/1060.77)
#define C_s6 (tuned/1123.85)
#define D_6 (tuned/1190.68)
#define E_6 (tuned/1336.49)
#define F_6 (tuned/1415.96)
#define F_s6 (tuned/1500.16)
#endif
