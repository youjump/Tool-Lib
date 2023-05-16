**方法：**

- <u>输入</u>指定格式的时间结构体和累加的秒数

  ```c
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
  ```

- <u>输出</u>为更新后的结构体



在线验证工具：

[时间计算器 - 在线工具 (try8.cn)](https://try8.cn/tool/time/calc)
