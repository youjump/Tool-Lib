#include <stdio.h>

typedef signed   char                   int8_t;      /**<  8bit integer type */
typedef signed   short                  int16_t;     /**< 16bit integer type */
typedef signed   int                    int32_t;     /**< 32bit integer type */
typedef unsigned char                   uint8_t;     /**<  8bit unsigned integer type */
typedef unsigned short                  uint16_t;    /**< 16bit unsigned integer type */
typedef unsigned int                    uint32_t;    /**< 32bit unsigned integer type */

typedef struct time_stamp
{
    uint8_t h_year;
    uint8_t l_year;
    uint8_t mon;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
} tm_t;

uint32_t leapyear_check (uint32_t y)
{
    if ((0 == y % 4 && y % 100 != 0) || y % 400 == 0)
        return 1;
    return 0;
}

tm_t add_tick_to_stamp (tm_t* t, uint32_t sec)
{
    const uint8_t month_buf[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    tm_t t_out;
    uint32_t min_add, hour_add, day_add, mon_add, year_add, day_temp, year_temp;

    t_out = *t;

    min_add = (t_out.sec + sec) / 60;
    t_out.sec = (t_out.sec + sec) % 60;

    hour_add = (t_out.min + min_add) / 60;
    t_out.min = (t_out.min + min_add) % 60;

    day_add = (t_out.hour + hour_add) / 24;
    t_out.hour = (t_out.hour + hour_add) % 24;

    mon_add = 0;
    day_temp = t_out.day;

    for (int i = t_out.mon - 1; ; i++)
    {
        int a = i % 12;

        year_temp = t_out.h_year * 100 + t_out.l_year + (i / 12);

        int temp = (a == 1 && leapyear_check(year_temp)) ? (month_buf[a] + 1) : month_buf[a];

        /* If we update the month, initial the day to the '1' */
        if (mon_add)
            day_temp = 1;

        if (day_add + day_temp > temp)
        {
            mon_add ++;
            day_add -= (temp - day_temp + 1);
        }
        else
        {
            t_out.day += day_add;
            break;
        }
    }

    year_add = (t_out.mon + mon_add) / 12;
    t_out.mon = (t_out.mon + mon_add) % 12;

    t_out.h_year = 20;
    t_out.l_year += year_add;

    return t_out;
}

int main(char* argv[], int argc)
{
    tm_t tt_in, tt_out;
    uint32_t add_sec = 31*86400;

    tt_out.h_year = 20;
    tt_out.l_year = 24;
    tt_out.mon = 1;
    tt_out.day = 1;
    tt_out.hour = 0;
    tt_out.min = 0;
    tt_out.sec = 0;

    tt_in = add_tick_to_stamp(&tt_out, add_sec);
    printf("%02d%02d-%02d-%02d %02d:%02d:%02d\n",
        tt_out.h_year, tt_out.l_year, tt_out.mon, tt_out.day, tt_out.hour, tt_out.min, tt_out.sec);
    printf("%02d%02d-%02d-%02d %02d:%02d:%02d\n",
        tt_in.h_year, tt_in.l_year, tt_in.mon, tt_in.day, tt_in.hour, tt_in.min, tt_in.sec);

    return 0;
}
