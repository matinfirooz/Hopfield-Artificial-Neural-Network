#include <stdio.h>
#include <math.h>  // شامل کتابخانه ریاضی برای توابع log2 و ceil
#include "1.xbm"
#include "2.xbm"
#include "3.xbm"
#include "4.xbm"
#include "5.xbm"
#include "6.xbm"
#include "7.xbm"
#include "8.xbm"
#include "9.xbm"
#include "10.xbm"

#define NEURONS 64  // تعریف تعداد نورون‌ها

int weights[NEURONS][NEURONS] = {0};  // مقداردهی ماتریس وزن‌ها با صفر
int recognize[NEURONS];  // آرایه‌ای برای ذخیره الگوی شناسایی
int patterns[10][NEURONS];  // آرایه‌ای برای ذخیره الگوها برای آموزش
int max_sum = 0;  // متغیر جهانی برای ذخیره حداکثر مجموع

// تابعی برای به‌روزرسانی حالت یک نورون
void update_neuron(int x, int *new_recognize) {
    int sum = 0;
    for (int i = 0; i < NEURONS; i++) {
        sum += weights[i][x] * recognize[i];  // محاسبه مجموع وزنی
    }
    if (sum > max_sum) {
        max_sum = sum;  // به‌روزرسانی حداکثر مجموع اگر مجموع کنونی بزرگتر باشد
    }
    new_recognize[x] = (sum >= 0) ? 1 : 0;  // به‌روزرسانی حالت نورون بر اساس مجموع
}

// تابعی برای وارد کردن الگوی تصویر به شبکه
void insert_img(int *pattern, char *x_bits) {
    for (int i = 0; i < NEURONS / 8; i++) {
        for (int j = 0; j < 8; j++) {
            pattern[i * 8 + j] = (x_bits[i] & (1 << (7 - j))) ? 1 : 0;  // تبدیل بیت‌ها به الگو
        }
    }
}

// تابعی برای آموزش شبکه با الگوی داده شده
void train(int *pattern) {
    for (int i = 0; i < NEURONS; i++) {
        for (int j = 0; j < NEURONS; j++) {
            if (i != j) {
                weights[i][j] += (2 * pattern[i] - 1) * (2 * pattern[j] - 1);  // به‌روزرسانی وزن‌ها بر اساس الگو
            }
        }
    }
}

// تابعی برای چاپ الگوی شناسایی کنونی
void print_pat(int *pattern) {
    for (int i = 0; i < NEURONS; i++) {
        if (i % 8 == 0) {
            printf("\n");
        }
        printf("[%d]", pattern[i]);  // چاپ حالت هر نورون
    }
    printf("\n");
}

// تابعی برای به‌روزرسانی حالت همه نورون‌ها
void update_all() {
    int new_recognize[NEURONS];
    for (int i = 0; i < 10; i++) {  // به‌روزرسانی برای 10 دوره
        for (int j = 0; j < NEURONS; j++) {
            update_neuron(j, new_recognize);  // به‌روزرسانی هر نورون
        }
        for (int k = 0; k < NEURONS; k++) {
            recognize[k] = new_recognize[k];  // کپی کردن حالت جدید به آرایه recognize
        }
        printf("Recognition pattern after update cycle %d:\n", i + 1);
        print_pat(recognize);  // چاپ الگوی به‌روزرسانی شده
    }
}

// تابعی برای محاسبه دقت شناسایی الگو
double calculate_accuracy(int *pattern1, int *pattern2) {
    int matches = 0;
    for (int i = 0; i < NEURONS; i++) {
        if (pattern1[i] == pattern2[i]) {
            matches++;  // شمارش تطابق‌ها بین دو الگو
        }
    }
    return (double)matches / NEURONS;  // بازگرداندن دقت به عنوان یک کسر
}

int main() {
    // تابع اصلی نمونه برای مقداردهی اولیه و اجرای شبکه
    char *x_bits[] = {_1_bits, _2_bits, _3_bits, _4_bits, _5_bits, _6_bits, _7_bits, _8_bits, _9_bits, _10_bits};  // فرض می‌کنیم img_bits در فایل‌های xbm موجود هستند
    for (int i = 0; i < 10; i++) {
        insert_img(patterns[i], x_bits[i]);  // وارد کردن الگوهای تصویری
        train(patterns[i]);  // آموزش شبکه با هر الگو
    }
    update_all();  // به‌روزرسانی حالت شبکه
    printf("Maximum sum encountered: %d\n", max_sum);  // چاپ حداکثر مجموع

    // محاسبه تعداد بیت‌های مورد نیاز برای نمایش حداکثر مجموع
    int bits_required = (int)ceil(log2(max_sum + 1));
    printf("Number of bits required to represent the maximum sum: %d\n", bits_required);

    return 0;
}
