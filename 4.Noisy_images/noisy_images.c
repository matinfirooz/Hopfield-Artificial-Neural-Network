#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WIDTH 8       // عرض تصویر
#define HEIGHT 8      // ارتفاع تصویر
#define NUM_IMAGES 10 // تعداد تصاویر اصلی
#define NOISE_LEVEL 0.05 // سطح نویز (5 درصد)
#define NUM_NOISY_IMAGES 8 // تعداد تصاویر نویزی که باید تولید شوند

// تابعی برای اضافه کردن نویز به تصویر
void add_noise(char *image_bits, int width, int height, float noise_level) {
    int num_pixels = width * height; // تعداد کل پیکسل‌ها
    int num_noisy_pixels = (int)(num_pixels * noise_level); // تعداد پیکسل‌هایی که باید نویزی شوند
    
    // تولید نویز برای تعداد مشخصی از پیکسل‌ها
    for (int i = 0; i < num_noisy_pixels; i++) {
        int rand_index = rand() % num_pixels; // انتخاب پیکسل تصادفی
        image_bits[rand_index / 8] ^= (1 << (rand_index % 8)); // تغییر مقدار پیکسل
    }
}

// تابعی برای ذخیره تصویر نویزی به صورت فایل XBM
void save_noisy_image(char *image_bits, int width, int height, int image_index, int noise_index) {
    char filename[50]; // نام فایل
    sprintf(filename, "noisy_%d_%d.xbm", image_index + 1, noise_index + 1); // تنظیم نام فایل
    
    FILE *file = fopen(filename, "w"); // باز کردن فایل برای نوشتن
    if (file) {
        fprintf(file, "#define im_width %d\n", width); // نوشتن عرض تصویر
        fprintf(file, "#define im_height %d\n", height); // نوشتن ارتفاع تصویر
        fprintf(file, "static char noisy_%d_%d_bits[] = {\n", image_index + 1, noise_index + 1); // شروع آرایه داده‌های تصویر
        
        // نوشتن داده‌های تصویر به صورت هگزادسیمال
        for (int i = 0; i < (width * height) / 8; i++) {
            fprintf(file, "0x%02x", image_bits[i] & 0xFF);
            if (i < (width * height) / 8 - 1) {
                fprintf(file, ",");
            }
        }
        
        fprintf(file, "\n};\n"); // پایان آرایه داده‌های تصویر
        fclose(file); // بستن فایل
    }
}

int main() {
    srand(time(NULL)); // تنظیم مقدار اولیه برای تولید اعداد تصادفی
    
    for (int i = 0; i < NUM_IMAGES; i++) { // حلقه برای هر تصویر اصلی
        char image_bits[WIDTH * HEIGHT / 8]; // آرایه برای ذخیره داده‌های تصویر اصلی
        
        // بارگذاری داده‌های تصویر از فایل
        char filename[20];
        sprintf(filename, "%d.xbm", i + 1); // تنظیم نام فایل
        FILE *file = fopen(filename, "r"); // باز کردن فایل برای خواندن
        if (file) {
            char buffer[100];
            int byte_index = 0;
            while (fgets(buffer, sizeof(buffer), file)) { // خواندن خطوط فایل
                if (buffer[0] == '0' && buffer[1] == 'x') { // بررسی اینکه آیا خط شامل داده‌های تصویر است
                    sscanf(buffer, "%hhx", &image_bits[byte_index]); // تبدیل داده‌های هگزادسیمال به باینری و ذخیره در آرایه
                    byte_index++;
                }
            }
            fclose(file); // بستن فایل
        }
        
        // تولید تصاویر نویزی
        for (int j = 0; j < NUM_NOISY_IMAGES; j++) { // حلقه برای تعداد تصاویر نویزی
            char noisy_image_bits[WIDTH * HEIGHT / 8]; // آرایه برای ذخیره داده‌های تصویر نویزی
            memcpy(noisy_image_bits, image_bits, WIDTH * HEIGHT / 8); // کپی کردن داده‌های تصویر اصلی به آرایه نویزی
            add_noise(noisy_image_bits, WIDTH, HEIGHT, NOISE_LEVEL); // اضافه کردن نویز به تصویر
            save_noisy_image(noisy_image_bits, WIDTH, HEIGHT, i, j); // ذخیره تصویر نویزی به صورت فایل XBM
        }
    }
    
    return 0;
}


