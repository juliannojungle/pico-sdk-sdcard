#include <stdio.h>
#include <string.h>
#include <vector>

#include "pico/stdlib.h"
#include "rtc.h" // rtc for file's timestamp.
#include "f_util.h" // FS functions and declarations.
#include "hw_config.h" // no-OS-FatFS declarations

static std::vector<spi_t *> spis;
static std::vector<sd_card_t *> sd_cards;

/* BEGIN no-OS-FatFS implementations */
size_t sd_get_num() {
    return sd_cards.size();
}

sd_card_t *sd_get_by_num(size_t num) {
    if (num <= sd_get_num()) {
        return sd_cards[num];
    } else {
        return NULL;
    }
}

size_t spi_get_num() {
    return spis.size();
}

spi_t *spi_get_by_num(size_t num) {
    if (num <= spi_get_num()) {
        return spis[num];
    } else {
        return NULL;
    }
}

void add_spi(spi_t *spi) {
    spis.push_back(spi);
}

void add_sd_card(sd_card_t *sd_card) {
    sd_cards.push_back(sd_card);
}

void SetupSpi() {
    spi_t *p_spi = new spi_t;
    memset(p_spi, 0, sizeof(spi_t));

    if (!p_spi) panic("Out of memory");

    p_spi->hw_inst = spi0;
    p_spi->miso_gpio = 16;
    p_spi->mosi_gpio = 19;
    p_spi->sck_gpio = 18;
    p_spi->baud_rate = 25 * 1000 * 1000;  // Actual frequency: 20833333.
    add_spi(p_spi);
}

void SetupSdCard() {
    sd_card_t *p_sd_card = new sd_card_t;
    memset(p_sd_card, 0, sizeof(sd_card_t));

    if (!p_sd_card) panic("Out of memory");

    p_sd_card->pcName = "0:";
    p_sd_card->type = SD_IF_SPI,
    p_sd_card->spi_if.spi = spi_get_by_num(0);
    p_sd_card->spi_if.ss_gpio = 17;
    p_sd_card->use_card_detect = true;
    p_sd_card->card_detect_gpio = 20;
    p_sd_card->card_detected_true = 0; // What the GPIO_read returns when a card is present.
    add_sd_card(p_sd_card);
}
/* END no-OS-FatFS implementations */

void test(sd_card_t *pSD) {
    printf("mounting sdcard...\n");
    FRESULT result = f_mount(&pSD->fatfs, pSD->pcName, 1);

    if (FR_OK != result) {
        printf("f_mount error: %s (%d)\n", FRESULT_str(result), result);
        return;
    }

    printf("setting current drive...\n");
    result = f_chdrive(pSD->pcName);

    if (FR_OK != result) {
        printf("f_chdrive error: %s (%d)\n", FRESULT_str(result), result);
        f_unmount(pSD->pcName);
        return;
    }

    printf("opening file...\n");
    FIL file;
    const char *const filename = "teste.txt";
    result = f_open(&file, filename, FA_OPEN_APPEND | FA_READ | FA_WRITE);

    if (FR_OK != result && FR_EXIST != result) {
        printf("f_open(%s) error: %s (%d)\n", filename, FRESULT_str(result), result);
        f_unmount(pSD->pcName);
        return;
    }

    printf("writing file...\n");
    f_rewind(&file);
    f_truncate(&file);

    for (int i = 0; i < 10; i++) {
        if (f_puts("This line was appended!\n", &file) < 0) {
            printf("f_printf failed\n");
        }
    }

    // TODO: read
    // f_sync(&file);
    // printf("reading file...\n");
    // f_rewind(&file);
    // char * buffer[4096];
    // UINT bytesRead = 4096;

    // while (bytesRead > 0) {
    //     result = f_read(&file, buffer, sizeof buffer, &bytesRead);

    //     if (result == FR_OK) {
    //         printf("%s", buffer);
    //     }
    // }

    printf("closing file...\n");
    result = f_close(&file);

    if (FR_OK != result) {
        printf("f_close error: %s (%d)\n", FRESULT_str(result), result);
    }

    printf("unmounting sdcard...\n");
    f_unmount(pSD->pcName);
}

int main() {
    stdio_init_all();
    time_init();

    sleep_ms(3000);
    puts("starting.");

    SetupSpi();
    SetupSdCard();

    for (size_t i = 0; i < sd_get_num(); ++i) {
        test(sd_get_by_num(i));
    }

    while(true) {
    }
}