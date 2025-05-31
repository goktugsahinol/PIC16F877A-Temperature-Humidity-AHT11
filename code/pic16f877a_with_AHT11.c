#include <16F877A.h>
#fuses HS, NOWDT, NOPUT, NOLVP
#use delay(clock=20000000)
#use i2c(master, SDA=PIN_B0, SCL=PIN_B1, FAST)

#define LCD_ENABLE_PIN PIN_C2
#define LCD_RS_PIN     PIN_C0
#define LCD_RW_PIN     PIN_C1
#define LCD_DATA4      PIN_D4
#define LCD_DATA5      PIN_D5
#define LCD_DATA6      PIN_D6
#define LCD_DATA7      PIN_D7
#include <lcd.c>

void aht10_init() {
    i2c_start();
    i2c_write(0x70); // AHT11 adresi  bu adresi deðiþtirebilirsiniz bazý modeller 0x38 adresini kullanýr
    i2c_write(0xBE); // Soft reset komutu
    i2c_stop();
    delay_ms(20);    // Sensör hazýr olana kadar bekle
}

void aht10_trigger_measurement() {
    i2c_start();
    i2c_write(0x70); // AHT10 adresi yazma modu
    i2c_write(0xAC); // Trigger measurement
    i2c_write(0x33);
    i2c_write(0x00);
    i2c_stop();
    delay_ms(80); // Ölçüm tamamlanmasý için bekle
}

int1 aht10_read(float *sicaklik, float *nem) {
    int8 data[6];
    int32 raw_temp, raw_hum;

    i2c_start();
    i2c_write(0x71); // AHT10 adresi okuma modu
    for (int i = 0; i < 6; i++) {
        data[i] = i2c_read(i < 5); // Son baytta NOACK
    }
    i2c_stop();

    // Ölçüm bitmiþ mi kontrol et
    if ((data[0] & 0x80) == 0x80)
        return 0; // Ölçüm devam ediyor, baþarýsýz

    raw_hum = ((int32)data[1] << 12) | ((int32)data[2] << 4) | (data[3] >> 4);
    raw_temp = (((int32)(data[3] & 0x0F)) << 16) | ((int32)(data[4]) << 8) | data[5];

    *nem = (raw_hum * 100.0) / 1048576.0;
    *sicaklik = (raw_temp * 200.0 / 1048576.0) - 50.0;

    return 1; // Baþarýlý
}

void main() {
    float sicaklik = 0.0, nem = 0.0;

    lcd_init();
    lcd_putc("\fAHT10 Baslatiliyor");
    delay_ms(1000);

    aht10_init();
    lcd_putc("\f");

    while (TRUE) {
        aht10_trigger_measurement();
        if (aht10_read(&sicaklik, &nem)) {
            lcd_gotoxy(1,1);
            printf(lcd_putc, "Sicaklik: %2.1f C", sicaklik);
            lcd_gotoxy(1,2);
            printf(lcd_putc, "Nem: %2.1f %%", nem);
        } else {
            lcd_putc("\fSensor Hatasi");
        }
        delay_ms(2000); // 2 saniyede bir güncelle
    }
}
