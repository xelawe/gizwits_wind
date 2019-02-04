#define btnpin 4
#define ledpinbl 13
#define ledpinrt 15
#define ledpingn 12

void set_rgb(int iv_red, int iv_green, int iv_blue) {

  int lv_green = iv_green * 0.8;
  int lv_red = iv_red;
  int lv_blue = iv_blue;

  analogWrite(ledpinrt, lv_red);
  analogWrite(ledpingn, lv_green);
  analogWrite(ledpinbl, lv_blue);
}
