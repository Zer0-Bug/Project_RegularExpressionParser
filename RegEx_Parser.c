#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* ##################################################################################################################################### */

void dividerControl(const char *text, const char *input) {
    char wordsArray[10][10];
    int wordCount = 0;  // Dizi içindeki kelime sayısını tutar
    char buffer[10] = {0};  // Kelimeyi geçici olarak tutar
    int bufferIndex = 0;  // Buffer'ın indeksini tutar
    
    // `|` işaretine göre kelimeleri ayır
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '|') {
            // '|' ile karşılaştığında, buffer'daki kelimeyi dizine ekle
            buffer[bufferIndex] = '\0';  // Null sonlandırıcı ekle
            strcpy(wordsArray[wordCount], buffer);  // Kelimeyi diziye kopyala
            wordCount++;  // Dizi içindeki kelime sayısını artır
            bufferIndex = 0;  // Buffer'ı sıfırla
        } 
        
        else {
            buffer[bufferIndex++] = input[i];  // Karakteri buffer'a ekle
        }

    }
    
    // Son kelimeyi de ekle (input sonunda '|' yoksa atlanmaması için)
    buffer[bufferIndex] = '\0';  // Null sonlandırıcı ekle
    strcpy(wordsArray[wordCount], buffer);  // Kelimeyi diziye kopyala
    wordCount++;  // Dizi içindeki kelime sayısını artır
    
    // Metin içinde kelimeleri kontrol et
    int found = 0;  // Eşleşme olup olmadığını kontrol etmek için
    for (int i = 0; i < wordCount; i++) {
        if (strstr(text, wordsArray[i]) != NULL) {
            printf("%s is Found!\n", wordsArray[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No matches found.\n");
    }
}

/* ##################################################################################################################################### */

void generateWords(char wordsArray[10][10], const char *pattern, int *wordCount) {
    int i = 0;
    char preBracket[10] = {0};  // Parantezden önceki kısmı saklamak için
    char postBracket[10] = {0}; // Parantezden sonraki kısmı saklamak için
    int inBrackets = 0;         // Parantez içindeysek

    // Şablondaki parçaları oluşturmak için parantez durumunu kontrol et
    int preBracketLen = 0;

    while (pattern[i] != '\0') {

        if (pattern[i] == '(') {

            inBrackets = 1;  // Parantez içindeyiz
            int j = i + 1;
            int index = 0;  // Dizideki kelime oluşturma indeksi
            // Parantez içindeki seçenekler

            while (pattern[j] != ')' && pattern[j] != '\0') {

                wordsArray[index][0] = '\0';  // Kelimeyi temizle
                // Önce parantez öncesi kısmı ekle
                strcpy(wordsArray[index], preBracket);
                int len = strlen(wordsArray[index]);
                wordsArray[index][len] = pattern[j]; // Parantez içindeki karakteri ekle
                wordsArray[index][len + 1] = '\0'; // Null terminatör ekle
                (*wordCount)++; // Kelime sayısını artır
                index++; // Yeni kelime oluşturmak için
                j++; // Parantez içi sonraki karaktere geç

            }

            // Parantez içindeki işleme bitince, postBracket'ı al
            if (pattern[j] == ')') {
                strcpy(postBracket, &pattern[j + 1]); // Parantez sonrası kısmı ekle
            }
            break; // Parantez bitince, döngüyü sonlandır
        } 
        
        else {
            // Parantez dışındaysa, ön kısmı oluştur
            preBracket[preBracketLen++] = pattern[i];
            preBracket[preBracketLen] = '\0';
        }

        i++; // Sonraki karaktere geç
    }

    // Parantez sonrası kısmı ekle
    for (int k = 0; k < *wordCount; k++) {
        strcat(wordsArray[k], postBracket);
    }

}

void dividerAndBracketsControl(const char *text, const char *pattern) {
    // Şablondan olasılıkları oluşturmak için bir dizi
    char wordsArray[10][10] = {0};
    int wordCount = 0;  // Dizi içindeki kelime sayısı
    

    // Şablona göre kelimeleri oluştur
    generateWords(wordsArray, pattern, &wordCount);


    // Metni olasılıklara göre kontrol et
    int found = 0;  // Eşleşme olup olmadığını kontrol etmek için
    for (int k = 0; k < wordCount; k++) {
        if (strstr(text, wordsArray[k]) != NULL) {
            printf("%s is Found!\n", wordsArray[k]);
            found = 1;
        }
    }

    if (!found) {
        printf("No matches found.\n");
    }
}



/* ##################################################################################################################################### */

#define MAX_WORDS 50
#define MAX_WORD_LEN 50

void generWords(const char *pattern, char wordsArray[MAX_WORDS][MAX_WORD_LEN], int *wordsCount) {

    int len = strlen(pattern);
    int wordIndex = 0;

    for (int i = 0; i < len; i++) {

        if (pattern[i] == '[') {
            // Köşeli parantezin sonunu bul
            int bracketEnd = i + 1;
            while (bracketEnd < len && pattern[bracketEnd] != ']') {
                bracketEnd++;
            }

            // Köşeli parantez içindeki harfleri işle
            for (int j = i + 1; j < bracketEnd; j++) {
                char currentWord[MAX_WORD_LEN] = {0};

                // Başlangıç kısmını ve köşeli parantez içindeki harfi al
                strncpy(currentWord, pattern, i);
                currentWord[i] = pattern[j];
                strcpy(currentWord + i + 1, pattern + bracketEnd + 1);

                strncpy(wordsArray[wordIndex], currentWord, MAX_WORD_LEN - 1);
                wordsArray[wordIndex][MAX_WORD_LEN - 1] = '\0';  // Güvenlik için sonlandırıcı ekleyin
                wordIndex++;
            }

            i = bracketEnd;  // Köşeli parantezin sonrasına atla
        }
    }

    *wordsCount = wordIndex;
}


void squareBracketsControl(const char *pattern, const char *input) {

    char wordsArray[MAX_WORDS][MAX_WORD_LEN];
    int wordsCount = 0;

    generWords(pattern, wordsArray, &wordsCount);

    // input'u virgül ile ayırma
    char inputCopy[MAX_WORD_LEN * MAX_WORDS];
    strncpy(inputCopy, input, sizeof(inputCopy));
    inputCopy[sizeof(inputCopy) - 1] = '\0';
    
    char *token = strtok(inputCopy, ", ");  // Virgül ve boşluk ile ayırma
    int found = 0;

    while (token != NULL) {

        for (int i = 0; i < wordsCount; i++) {

            if (strcmp(wordsArray[i], token) == 0) {
                printf("%s is Found!\n", wordsArray[i]);
                found = 1;
                break;
            }

        }

        token = strtok(NULL, ", ");  // Sonraki kelimeyi alın
    }

    if (!found) {
        printf("Nothing found!\n");
    }
}

/* ##################################################################################################################################### */

void parsePattern(const char *pattern, char result[][20], int *count) {

    int len = strlen(pattern);
    int resCount = 0;
    char temp[20]; // Geçici kelime oluşturucu
    int tempIndex = 0;
    
    for (int i = 0; i < len; i++) {

        if (pattern[i] == '[') {

            // Alternatif karakterler kümesini işleme
            int j = i + 1;
            while (j < len && pattern[j] != ']') {
                temp[tempIndex] = pattern[j]; // Parantez içindeki her bir harfi al
                temp[tempIndex + 1] = '\0'; // Stringi sonlandır
                strcpy(result[resCount], temp); // Oluşan kelimeyi kaydet
                resCount++;
                j++;
            }

            i = j; // ']' işaretinden sonra devam et
        } 
        
        else if (pattern[i] == '\\' && i + 1 < len && pattern[i + 1] == '*') {
            // Kaçış karakteri ve '*' sembolü için
            for (int k = 0; k < resCount; k++) {
                strcat(result[k], "*");
            }

            i++; // '\\*' sembolünü atla
        } 
        
        else {
            // Normal bir karakterse, tüm kelimelere ekle
            for (int k = 0; k < resCount; k++) {
                int length = strlen(result[k]);
                result[k][length] = pattern[i]; // Karakter ekle
                result[k][length + 1] = '\0'; // String sonlandır
            }

            if (resCount == 0) { // Eğer henüz kelime eklenmediyse
                temp[tempIndex] = pattern[i];
                temp[tempIndex + 1] = '\0';
                strcpy(result[0], temp);
                resCount++;
            }
        }
    }

    *count = resCount; // Olası kelime sayısını güncelle
}

void squareBracketsAndSlashControl(const char *text, const char *input) {
    char wordsArray[20][20];
    int wordCount = 0;

    parsePattern(input, wordsArray, &wordCount);

    // Oluşan kelimeleri giriş metninde arama
    for (int i = 0; i < wordCount; i++) {

        if (strstr(text, wordsArray[i]) != NULL) {

            printf("%s is Found!\n", wordsArray[i]);
        }
    }

}

/* ##################################################################################################################################### */

void squareBracketsAndHyphenControl(const char *text, const char *input) {
    int allowed[256] = {0}; // 256 farklı karakter için tablo
    int len = strlen(input);

    // input'tan harfleri ve aralıkları belirle
    for (int i = 0; i < len; i++) {

        if (isalpha(input[i])) {

            if (i + 2 < len && input[i + 1] == '-') {

                // aralık belirtildi, örneğin: a-z
                for (char c = input[i]; c <= input[i + 2]; c++) {
                    allowed[(int)c] = 1;
                }

                i += 2; // ilerlemeyi 2 artır, çünkü aralığı işledik

            } 
            
            else {
                // tek harf belirtildi
                allowed[(int)input[i]] = 1;
            }
        }
    }

    // metinde yalnız başına duran uygun harfleri bul
    int text_len = strlen(text);
    for (int i = 0; i < text_len; i++) {

        if (allowed[(int)text[i]]) {
            int isSeparate = 1;

            // harfin sol ve sağında harf veya rakam olmamalı
            if (i > 0 && (isalpha(text[i - 1]) || isdigit(text[i - 1]))) {
                isSeparate = 0;
            }

            if (i < text_len - 1 && (isalpha(text[i + 1]) || isdigit(text[i + 1]))) {
                isSeparate = 0;
            }

            if (isSeparate) {
                printf("%c is Found!\n", text[i]);
            }
        }
    }

    printf("\n");
}

/* ##################################################################################################################################### */

// Köşeli parantez içindeki aralıkları eklemek için yardımcı fonksiyon
void addRange(char start, char end, char *array, int *index) {

    for (char c = start; c <= end; c++) {
        array[*index] = c;
        (*index)++;
    }

}

// Kullanıcı girdisini virgüllerle ayırmak için fonksiyon
void splitInput(const char *input, char inputArray[][50], int *numWords) {
    int j = 0;
    *numWords = 0;

    for (int i = 0; input[i] != '\0'; i++) {

        if (input[i] == ',') {

            inputArray[*numWords][j] = '\0';  // Bu kelimenin sonunu belirler
            (*numWords)++;
            j = 0;  // Yeni kelime için sıfırdan başlar
        } 
        
        else {
            inputArray[*numWords][j++] = input[i];
        }
    }

    if (j > 0) {  // Son kelimeyi eklemek için kontrol
        inputArray[*numWords][j] = '\0';
        (*numWords)++;
    }
}

// Dizedeki baştaki ve sondaki boşlukları temizleyen yardımcı fonksiyon
void trim(char *str) {
    // Baştaki boşlukları temizle
    int start = 0;

    while (isspace(str[start])) {
        start++;
    }

    // Sondaki boşlukları temizle
    int end = strlen(str) - 1;
    while (end >= start && isspace(str[end])) {
        end--;
    }

    // Boşlukları ortadan kaldır
    for (int i = 0; i <= (end - start); i++) {
        str[i] = str[start + i];
    }
    str[end - start + 1] = '\0';  // Dizenin sonunu belirle
}

// Ana fonksiyon: Olası kelimeleri analiz eder ve kullanıcı girdisi ile karşılaştır
void squareBracketsAndHyphenAndDividerControl(const char *text, const char *input) {

    char leftBracketContent[50];  // Köşeli parantez içeriği
    int lIndex = 0;

    char rightPart[50];           // "|" sonrası sağ kısmı
    int rIndex = 0;

    int i = 0;
    int isLeftBracket = 0;

    // Diziyi analiz ederek köşeli parantezleri işle
    while (text[i] != '\0') {

        if (text[i] == '|') {
            isLeftBracket = 1;
            i++;
            continue;
        }

        if (isLeftBracket) {
            rightPart[rIndex++] = text[i];
        } 
        
        else {
            if (text[i] == '[') {
                i++;

                while (text[i] != ']' && text[i] != '\0') {

                    if (text[i + 1] == '-' && text[i + 2] != '\0') {
                        addRange(text[i], text[i + 2], leftBracketContent, &lIndex);
                        i += 2;  // Aralıkta iki adım ilerle

                    }
                    
                    else {
                        leftBracketContent[lIndex++] = text[i];
                    }

                    i++;
                }
            }
        }

        i++;
    }

    rightPart[rIndex] = '\0';  // Sağ kısmın sonunu belirler

    // Olası kelimeleri saklayan bir dizi
    char wordsArray[50][50];
    int wordsIndex = 0;

    for (int j = 0; j < lIndex; j++) {
        snprintf(wordsArray[wordsIndex], 50, "%c%s", leftBracketContent[j], "at");
        wordsIndex++;
    }

    // Sağ kısmı kelime olarak ekle
    snprintf(wordsArray[wordsIndex], 50, "%s", rightPart);
    wordsIndex++;

    // Kullanıcı girdisini virgüllerle ayır
    char inputArray[50][50];
    int numWords = 0;
    splitInput(input, inputArray, &numWords);

    // Eşleşmeleri kontrol et
    int found = 0;

    for (int k = 0; k < numWords; k++) {
        
        trim(inputArray[k]);  // Boşlukları temizle
        
        for (int t = 0; t < wordsIndex; t++) {
            
            if (strcmp(inputArray[k], wordsArray[t]) == 0) {
                printf("%s is Found!\n", wordsArray[t]);
                found = 1;
            }

        }

    }


    if (!found) {
        printf("Nothing found!\n");
    }
}

/* ##################################################################################################################################### */

void questionMarkControl(const char *text, const char *input) {

    char wordsArray[2][100];

    int index = -1;
    int length = strlen(input);


    // Soru işaretinin konumunu bul
    for (int i = 0; i < length; i++) {

        if (input[i] == '?') {
            index = i;
            break;
        }

    }


    // Soru işaretini kaldırarak ilk kelimeyi oluştur
    strncpy(wordsArray[0], input, index);
    wordsArray[0][index] = '\0';
    strcat(wordsArray[0], input + index + 1);  // Sonraki karakterleri ekle

    // Soru işareti ve bir önceki karakteri kaldırarak kelime oluşturmaya devam et
    strncpy(wordsArray[1], input, index - 1);
    wordsArray[1][index - 1] = '\0';
    strcat(wordsArray[1], input + index + 1);  // Sonraki karakterleri ekle

    // text içinde wordsArray'deki kelimeleri kontrol et
    int found = 0;
    for (int i = 0; i < 2; i++) {

        if (strstr(text, wordsArray[i])) {  // text içinde kelimeyi ara
            printf("%s is Found!\n", wordsArray[i]);
            found = 1;
        }

    }


    if (!found) {
        printf("Nothing Found!");
    }
}


/* ##################################################################################################################################### */


// Girdi metnindeki ön ve son boşlukları temizler
void trimComma(char *str) {
    int len = strlen(str);
    
    // Son boşlukları kaldır
    while (len > 0 && isspace(str[len - 1])) {
        str[--len] = '\0';
    }
    
    // İlk boşlukları kaldır
    int start = 0;
    while (isspace(str[start])) {
        start++;
    }
    
    if (start > 0) {
        // Boşlukları temizlemek için diziyi sola kaydır
        memmove(str, str + start, len - start + 1);
    }
}


void generateVariations(const char *text, char wordsArray[][100], int *count) {

    char currentWord[100] = {0};
    int wordIndex = 0;
    *count = 0;

    // Varyasyonları oluştururken '*' işaretine dikkat etmek lazım
    for (int i = 0; i < strlen(text); i++) {

        if (text[i] == '*') {
            char repeatedChar = text[i - 1];
            int originalLength = wordIndex;

            for (int j = 0; j <= 10; j++) {
                wordIndex = originalLength;

                for (int k = 0; k < j; k++) {
                    currentWord[wordIndex++] = repeatedChar;
                }

                for (int l = i + 1; l < strlen(text); l++) {
                    currentWord[wordIndex++] = text[l];
                }

                currentWord[wordIndex] = '\0';
                strcpy(wordsArray[*count], currentWord);
                (*count)++;
            }

            break; // '*' ile ilgili varyasyonlar tamamlandığında çık

        } 
        
        else {
            currentWord[wordIndex++] = text[i];
        }

    }
}

void starControl(const char *text, const char *input) {
    char wordsArray[11][100] = {0};
    int count = 0;

    // Olası varyasyonları oluştur
    generateVariations(text, wordsArray, &count);

    // Girdiyi virgülle ayırırken boşlukları temizle
    char inputCopy[256];
    strcpy(inputCopy, input);

    char *token = strtok(inputCopy, ",");
    int found = 0;
    
    while (token != NULL) {

        trimComma(token); // Boşlukları temizle
        
        for (int i = 0; i < count; i++) {

            if (strcmp(token, wordsArray[i]) == 0) {
                printf("%s is Found!\n", wordsArray[i]);
                found = 1;
                break;
            }

        }

        token = strtok(NULL, ",");
    }
            
    if (!found) {
        printf("Nothing found!\n", token);
    }
}


/* ##################################################################################################################################### */


// "+" işaretinden sonra gelen harfi tekrarlayarak olasılıkları oluşturur
void variationsGen(const char *text, char wordsArray[][100], int *count) {
    char prefix[100] = {0}; // "+" öncesi
    char repeatChar = 0;    // "+" sonrası tekrarlanan harf
    char suffix[100] = {0}; // "+" sonrası
    int prefixLen = 0;
    int suffixLen = 0;
    int foundPlus = 0;

    int i = 0;

    // Metni tarayarak "+" işaretini bul ve onu doğru şekilde ayır
    while (text[i] != '\0') {

        if (text[i] == '+') {
            foundPlus = 1;
            repeatChar = text[i - 1]; // "+" işaretinden önceki harfi tekrarlayacağız
            i++; // "+" işaretini geç

        }
        
        else if (!foundPlus) {
            prefix[prefixLen++] = text[i];
            i++;
        }
        
        else {
            suffix[suffixLen++] = text[i];
            i++;
        }

    }

    prefix[prefixLen] = '\0';
    suffix[suffixLen] = '\0';

    // İlk olasılık: gogle (tek tekrar)
    strcpy(wordsArray[*count], prefix);
    strcat(wordsArray[*count], suffix);
    (*count)++;

    // Diğer olasılıklar
    for (int j = 2; j <= 10; j++) {
        strcpy(wordsArray[*count], prefix);

        // Repeat harfini 'j' kez ekle
        for (int k = 0; k < j; k++) {
            strncat(wordsArray[*count], &repeatChar, 1);
        }

        // Suffix'i ekle
        strcat(wordsArray[*count], suffix);

        (*count)++;
    }
}

// Girdideki kelimeleri olasılıklar ile karşılaştırır
void plusControl(const char *text, const char *input) {
    char wordsArray[11][100] = {0}; // 11 olasılık oluştur (1'den 10'a kadar)
    int count = 0;

    // Olasılıkları oluştur
    variationsGen(text, wordsArray, &count);

    // Input'u virgüllerle ayır
    char inputCopy[256];
    strcpy(inputCopy, input);

    char *token = strtok(inputCopy, ",");

    int found = 0;
    while (token != NULL) {
        // Boşlukları temizlemek için
        while (*token == ' ') {
            token++;
        }


        // Varyasyonları input ile karşılaştır
        for (int i = 0; i < count; i++) {

            if (strcmp(token, wordsArray[i]) == 0) {
                printf("%s is Found!\n", wordsArray[i]);
                found = 1;
                break;
            }

        }

        token = strtok(NULL, ",");
    }

    if (!found) {
        printf("Nothing found!\n");
    }
}

/* ##################################################################################################################################### */

// Boşlukları temizlemek için bir yardımcı fonksiyon
void triM(char *str) {

    int len = strlen(str);
    
    // String'in sonundaki boşlukları kaldır
    while (len > 0 && isspace(str[len - 1])) {
        str[--len] = '\0';
    }

    // String'in başındaki boşlukları kaldır
    int start = 0;
    while (start < len && isspace(str[start])) {
        start++;
    }

    if (start > 0) {
        memmove(str, str + start, len - start + 1);
    }
}

// "+" işaretine göre olasılıkları oluşturur
void gnrtVariations(const char *text, char wordsArray[][100], int *count) {
    char prefix[100] = {0}; // "+" öncesi
    char repeat[100] = {0}; // "+" sonrası parantez içi
    char suffix[100] = {0}; // "+" sonrası
    int prefixLen = 0;
    int repeatLen = 0;
    int suffixLen = 0;
    int foundPlus = 0;

    int i = 0;

    // Metni analiz ederek "+" işareti ve parantez içindeki kısmı ayır
    while (text[i] != '\0') {
        if (text[i] == '(') {
            // Parantez içindeki tekrar edilecek kısmı al
            i++;

            while (text[i] != ')' && text[i] != '\0') {
                repeat[repeatLen++] = text[i];
                i++;
            }

            repeat[repeatLen] = '\0';
            i++; // Parantez kapandığında sonraki karaktere geç

        }
        
        else if (text[i] == '+') {
            foundPlus = 1;
            i++; // "+" işaretini geç
        } 
        
        else if (!foundPlus) {
            // "+" işaretinden önceki kısmı al
            prefix[prefixLen++] = text[i];
            i++;
        } 
        
        else {
            // "+" işaretinden sonraki kısmı al
            suffix[suffixLen++] = text[i];
            i++;
        }
    }

    prefix[prefixLen] = '\0';
    suffix[suffixLen] = '\0';

    // "+" işareti için 1'den 10'a kadar tekrar varyasyonları oluştur
    *count = 0;
    for (int j = 1; j <= 10; j++) {
        strcpy(wordsArray[*count], prefix);

        // Tekrar eden kısmı 'j' kez ekle
        for (int k = 0; k < j; k++) {
            strcat(wordsArray[*count], repeat);
        }

        // Suffix'i ekle
        strcat(wordsArray[*count], suffix);

        (*count)++;
    }
}

// Girdideki kelimeleri olasılıklar ile karşılaştırır
void plusAndBracketsControl(const char *text, const char *input) {
    char wordsArray[10][100]; // 10 olasılık oluştur
    int count = 0;

    // Olasılıkları oluştur
    gnrtVariations(text, wordsArray, &count);

    // Inputu virgüller ile ayır
    char inputCopy[256];
    strcpy(inputCopy, input);

    char *token = strtok(inputCopy, ",");

    int found = 0;
    while (token != NULL) {
        triM(token); // Boşlukları temizle

        // Varyasyonları input ile karşılaştır
        for (int i = 0; i < count; i++) {
            if (strcmp(token, wordsArray[i]) == 0) {
                printf("%s is Found!\n", wordsArray[i]);
                found = 1;
                break;
            }
        }

        token = strtok(NULL, ",");
    }

    if (!found) {
        printf("Nothing found!\n");
    }
}

/* ##################################################################################################################################### */

// Girilen formatın "x{y,z}" veya "x{y,}" veya "x{y}" olmasını kontrol eder.
void extractPatternAndCounts(const char *input, char *patternChar, int *min, int *max) {

    int len = strlen(input);
    int i = 0;

    // PatternChar'ı ve min ile max değerlerini ayrıştır
    while (i < len && isalpha(input[i])) {
        i++;
    }

    if (i > 0 && i < len && input[i] == '{' && input[len - 1] == '}') {

        *patternChar = input[i - 1];
        char numbers[20];
        strncpy(numbers, &input[i + 1], len - i - 2);
        numbers[len - i - 2] = '\0';

        char *commaPos = strchr(numbers, ',');

        if (commaPos) {
            *commaPos = '\0';
            *min = atoi(numbers);
            *max = atoi(commaPos + 1);
            
            if (*max == 0) {
                *max = 10; // max değeri varsayılan 10 yapıyoruz (işlem hızı için sonsuz değil de 10 kere yapayım dedim istersek arttırız)
            }
        } 
        
        else {
            // Tek sayı için
            *min = atoi(numbers);
            *max = *min;
        }

    }
}

void curlyBracketsControl(const char *text, const char *input) {

    char patternChar;
    int min = 0, max = 0;

    extractPatternAndCounts(input, &patternChar, &min, &max);

    int count = 0;
    int matchFound = 0;

    // Eşleşmeleri kontrol et
    for (int i = 0; text[i] != '\0'; i++) {

        if (text[i] == patternChar) {
            count++;
        } 
        
        else {

            if (count >= min && count <= max) {
                printf("%.*s is Found!\n", count, &text[i - count]);
                matchFound = 1;
            }
            count = 0; // Sıfırla

        }
    }

    // Sonunda da kontrol yap
    if (count >= min && count <= max) {
        printf("%.*s is Found!\n", count, &text[strlen(text) - count]);
        matchFound = 1;
    }

    if (!matchFound) {
        printf("Nothing found!\n");
    }
}

/* ##################################################################################################################################### */


int find_slash_D(const char *str) {

    int lenT = 11;


    int len = strlen(str);

    if (len != lenT) {
        return 0; // Uzunluk uygun değil
    }

    // İlk karaktere bakar
    if (str[0] == '1') {
        return 1; // Eşleşme bulundu
    }

    return 0; // Eşleşme bulunmadı
}

// Virgülle ayrılmış kelimelerde kontrol eder
void curlyBracketsAndSlash_d_Control(const char *text, const char *input) {
    char inputCopy[256];
    strcpy(inputCopy, input);

    char *token = strtok(inputCopy, ",");

    int found = 0;
    while (token != NULL) {
        // Başında boşlukları temizleyin
        while (*token == ' ') {
            token++;
        }

        // kontrol
        if (find_slash_D(token)) {
            printf("%s is Found!\n", token);
            found = 1;
        }

        token = strtok(NULL, ",");
    }

    if (!found) {
        printf("Nothing found!\n");
    }
}

/* ##################################################################################################################################### */


void slash_d_Control(const char *text) {

    int found = 0;  // Bir eşleşme olup olmadığını kontrol eder
    const char *delimiter = " ";  // Boşlukları ayırıcı olarak kullan
    char text_copy[256];  // Güvenli uzunlukta bir buffer
    strcpy(text_copy, text);  // Orijinal text'i değiştirilebilmek için kopyala


    char *token = strtok(text_copy, delimiter);  // İlk kelimeyi al

    while (token != NULL) {
        // Kelime içinde herhangi bir rakam olup olmadığını kontrol et
        int contains_digit = 0;

        for (int i = 0; i < strlen(token); i++) {
            if (isdigit(token[i])) {
                contains_digit = 1;  // Bir rakam bulundu
                break;
            }
        }

        if (contains_digit) {
            printf("%s is Found!\n", token);  // Eşleşen kelimeyi yazdır
            found = 1;  // Eşleşme bulundu
        }

        token = strtok(NULL, delimiter);  // Bir sonraki kelimeyi al
    }

    if (!found) {  // Eşleşme bulunmadıysa
        printf("Nothing found!\n");
    }
}

/* ##################################################################################################################################### */


void slash_n_Control(const char *text, const char *input) {
    // Girdi metnini newline ('\n') karakterine göre ayırmak için bir gösterge işlevi kullanıyoruz
    const char *delimiter = "\n";
    char buffer[256]; // Orijinali değiştirmeden girişi değiştirmek için geçici buffer
    strncpy(buffer, input, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0'; // null termination

    // İlk parçasını ayır ve döngü ile devam et
    char *token = strtok(buffer, delimiter);

    int found = 0; // Sonuç kontrol değişkeni

    while (token != NULL) {
        // Eşleşme varsa sonucu yazdır
        if (strstr(text, token)) {
            printf("%s is Found!\n", token);
            found = 1;
        }
        token = strtok(NULL, delimiter); // Sonraki parçayı al
    }

    if (!found) {
        printf("Nothing found!\n");
    }
}

/* ##################################################################################################################################### */

void dotControl(const char *text, const char *input) {
    int inputLength = strlen(input);
    int textLength = strlen(text);

    // Text'in kelimelerine ayırma
    char word[100];
    int wordIndex = 0;
    int found = 0;

    for (int i = 0; i <= textLength; i++) {

        if (text[i] == ' ' || text[i] == '\0') {

            word[wordIndex] = '\0'; // Kelimenin sonuna null koy
            
            if (wordIndex > 0) { // Kelime boş değilse kontrol et
                
                if (inputLength <= strlen(word)) { // Şablon kelimeden uzun olmamalı
                    int matches = 1;
                    
                    for (int j = 0; j < inputLength; j++) {
                        
                        if (input[j] != '.' && input[j] != word[j]) {
                            matches = 0; // Eşleşme yok
                            break;
                        }

                    }

                    if (matches) {
                        printf("%s is Found!\n", word);
                        found = 1;
                    }
                }
            }

            wordIndex = 0; // Yeni kelimeye geç
        } 
        
        else {
            word[wordIndex++] = text[i]; // Kelimeyi oluştur
        }
    }

    if (found == 0)  {
        printf("Nothing found!\n"); // Hiç eşleşme bulunamadıysa
    }
}

/* ##################################################################################################################################### */

void powerControl(const char *text, const char *input) {
    if (text == NULL || input == NULL) {
        printf("Invalid input!\n");
        return;
    }

    // Eğer input '^' ile başlamıyorsa
    if (input[0] != '^') {
        printf("Nothing found!\n");
        return;
    }

    // Karşılaştıracağımız prefix'i al
    const char *prefix = input + 1;

    // Text'i boşluklara göre ayır
    const char *delimiters = " ";
    char text_copy[256];
    strncpy(text_copy, text, sizeof(text_copy) - 1);
    text_copy[255] = '\0';  // Metni sonlandır

    char *token = strtok(text_copy, delimiters);
    int found = 0;

    // Metindeki her kelimeyi kontrol et
    while (token != NULL) {

        if (strncmp(token, prefix, strlen(prefix)) == 0) {
            printf("%s is Found!\n", token);
            found = 1;
        }

        token = strtok(NULL, delimiters);
    }

    if (!found) {
        printf("Nothing found!\n");
    }
}

/* ##################################################################################################################################### */

void powerAndDollarControl(const char *text, const char *input) {
    int length = strlen(input);

    // Girdi başlangıcı ve sonu '^' ve '$' mı kontrol et

    if (length >= 3 && input[0] == '^' && input[length - 1] == '$') {
        // Aradığımız kelime '^' ve '$' arasındaki kelime

        char keyword[256];
        strncpy(keyword, input + 1, length - 2);
        keyword[length - 2] = '\0';

        // Kelimeleri kontrol et
        const char *delimiter = " "; // Kelimeler arasındaki ayırıcı
        char textCopy[256]; // text kopyalanacak
        strncpy(textCopy, text, sizeof(textCopy) - 1);
        textCopy[sizeof(textCopy) - 1] = '\0';

        char *token = strtok(textCopy, delimiter);
        int found = 0;

        while (token != NULL) {

            if (strcmp(token, keyword) == 0) {
                printf("%s is Found!\n", token);
                found = 1;
            }

            token = strtok(NULL, delimiter);
        }

        if (!found) {
            printf("Nothing found!\n");
        }
    }
}

/* ##################################################################################################################################### */

// "text" içerisindeki kelimeleri kontrol edip, "input" kelimesi kalıbıyla biten bir kelime var mı
void dollarControl(const char *text, const char *input) {
    int len = strlen(input);
    if (input[len - 1] != '$') {
        printf("Input must end with '$'.\n");
        return;
    }

    // Arama kalıbını alıyoruz, '$' karakterinden önceki kısmı.
    char pattern[100];
    strncpy(pattern, input, len - 1);
    pattern[len - 1] = '\0';

    // "text" içindeki kelimeleri ayırmak için
    const char *delimiter = " ";
    char text_copy[1000]; // "text" değişkenini değiştirmemek için
    strncpy(text_copy, text, sizeof(text_copy) - 1);
    text_copy[sizeof(text_copy) - 1] = '\0';

    char *token = strtok(text_copy, delimiter);
    int found = 0;

    while (token != NULL) {
        int token_len = strlen(token);
        int pattern_len = strlen(pattern);

        // Eğer token pattern ile bitiyorsa
        if (token_len >= pattern_len && strcmp(&token[token_len - pattern_len], pattern) == 0) {
            printf("%s is Found!\n", token);
            found = 1;
        }

        token = strtok(NULL, delimiter);
    }

    if (!found) {
        printf("Nothing found!\n");
    }
}

/* ##################################################################################################################################### */

// Bir kelimenin izin verilmeyen karakterlerden herhangi birini içerip içermediğini kontrol eden yardımcı fonksiyon
int containsDisallowedChar(const char *word, const char *disallowed) {
    while (*word) {
        if (strchr(disallowed, *word)) {
            return 1;  // İzin verilmeyen bir karakter içeriyor
        }
        word++;
    }
    return 0;  // İzin verilmeyen herhangi bir karakter içermiyor
}

void exceptControl(const char *text, const char *input) {
    // Metni kelimelere böl
    char textCopy[256];
    strncpy(textCopy, text, sizeof(textCopy) - 1);
    textCopy[sizeof(textCopy) - 1] = '\0';

    char *token = strtok(textCopy, " ");  // Split spaces
    int found = 0;

    while (token != NULL) {
        if (!containsDisallowedChar(token, input)) {
            printf("%s is Found!\n", token);  // İzin verilmeyen karakterler içermeyen kelime bulundu
            found = 1;  // En az bir kelime bulundu
        }
        token = strtok(NULL, " ");  // sonraki kelime
    }

    if (!found) {
        printf("Nothing found!\n");  // Kriterlere uyan kelime yok
    }
}

/* ##################################################################################################################################### */

void upperCaseControl(const char *text, const char *input) {
    // Kelimeleri ayırmak için bir ayırıcı kümesi
    const char *delimiters = " \t\n"; // Boşluk, sekme ve yeni satır

    // Metni değiştirmeden kopyala (strtok kullanacağız)
    char textCopy[256];
    strncpy(textCopy, text, sizeof(textCopy));
    textCopy[sizeof(textCopy) - 1] = '\0';

    // strtok
    char *token = strtok(textCopy, delimiters);
    int found = 0;

    // Kelimeler üzerinde döngü
    while (token != NULL) {

        // Eğer kelime büyük harfle başlıyorsa
        if (isupper(token[0])) {

            // Ve kullanıcının girdiği desene uyuyorsa
            if (strstr(input, "([A-Z])") != NULL && isalpha(token[0])) {
                printf("%s is Found!\n", token);
                found = 1;
            }

        }

        // Sonraki kelimeye geç
        token = strtok(NULL, delimiters);
    }

    if (!found) {
        printf("Nothing found!\n");
    }
}

/* ##################################################################################################################################### */

void wordControl(const char *text, const char *input) {
    // Kelimeleri ayırmak için bir kopya oluşturur
    char buffer[256];
    strcpy(buffer, text);

    // Kelimeleri ayırmak için boşluklar
    char *word = strtok(buffer, " ");
    int found = 0;

    while (word != NULL) {

        if (strcmp(word, input) == 0) {
            printf("%s is Found!\n", word);
            found = 1;
        }
        
        word = strtok(NULL, " ");
    }

    if (!found) {
        printf("Nothing found!\n");
    }
}

/* ##################################################################################################################################### */
/* ##################################################################################################################################### */
/* ##################################################################################################################################### */


int count_character(const char *str, char c) {
    int count = 0;
    while (*str) {
        if (*str == c) {
            count++;
        }
        str++;
    }
    return count;
}


/* ##################################################################################################################################### */
/* ##################################################################################################################################### */
/* ##################################################################################################################################### */
/* ##################################################################################################################################### */
/* ##################################################################################################################################### */
/* ##################################################################################################################################### */


int main() {

    const char *TEXT = "zzz, zzzz, zzzzz, zzzzzz, zzzzzzzz"; // Formatın uygun girilmesi gerekmektedir! Format düzgün girilmezse aranan eleman bulunamaz.
    // ^dog
    char input[33];
    printf("Search: ");
    scanf("%32s", input);


    int count_open_bracket = count_character(input, '(');
    int count_close_bracket = count_character(input, ')');
    int count_open_square_bracket = count_character(input, '[');
    int count_close_square_bracket = count_character(input, ']');
    int count_open_curly_bracket = count_character(input, '{');
    int count_close_curly_bracket = count_character(input, '}');




    // Question mark check
    if (strchr(input, '?')) {
            questionMarkControl(TEXT, input);       // DONE
            // colou?r
    }


/* ##################################################################################################################################### */

    else if (strchr(input, '^') && strchr(input, '*') && strchr(input, '&') && strchr(input, '@') && count_open_square_bracket > 0 && count_close_square_bracket > 0 && count_open_square_bracket == count_close_square_bracket) {
        exceptControl(TEXT, input);         // DONE
        // [^i*&2@]
    }


/* ##################################################################################################################################### */

    else if ((count_open_square_bracket > 0 && count_close_square_bracket > 0) && (count_open_bracket > 0 && count_close_bracket > 0) && (count_open_bracket == count_close_bracket) && (count_open_square_bracket == count_close_square_bracket) && strchr(input, '\\') && strchr(input, 'w')) {
        upperCaseControl(TEXT, input);      // DONE
        // ([A-Z])\w+
    }

/* ##################################################################################################################################### */


    // Divider check
    else if (strchr(input, '|') && count_open_square_bracket == 0 && count_close_square_bracket == 0) {
        
        if (strchr(input, '(') && strchr(input, ')') && count_open_bracket > 0 && count_close_bracket > 0 && count_open_bracket == count_close_bracket) {
            dividerAndBracketsControl(TEXT, input);     // DONE
            // gr(a|e)y
        }

        else {
            dividerControl(TEXT, input);        // DONE
            // gray|grey
        }

    }

/* ##################################################################################################################################### */

    // Square brackets check
    else if (count_open_square_bracket > 0 && count_close_square_bracket > 0 && count_open_square_bracket == count_close_square_bracket) {

        if (strchr(input, '\\')) {
            if (strchr(input, '*')) {
                squareBracketsAndSlashControl(input, TEXT);         // DONE
                // [Gg]o\*\*le
            }
        }


        else if (strchr(input, '-')) {

            if (strchr(input, '|')) {
                squareBracketsAndHyphenAndDividerControl(input, TEXT);      // DONE
                // [b-chm-pP]at|ot
            }

            else {
                squareBracketsAndHyphenControl(TEXT, input);        // DONE
                // [a-zA-Z]
            }

        }

        else {
            squareBracketsControl(input ,TEXT);     // DONE
            // b[aeiou]bble
        }
    }


/* ##################################################################################################################################### */

    // Star check
    else if (strchr(input, '*')) {

        starControl(input, TEXT);       // DONE
        // go*gle
    }

/* ##################################################################################################################################### */

    // Plus check
    else if (strchr(input, '+')) {

        if (count_open_bracket > 0 && count_close_bracket > 0 && count_open_bracket == count_close_bracket) {
            plusAndBracketsControl(input, TEXT);        // DONE
            // g(oog)+le
        }
        
        else {
            plusControl(input, TEXT);       // DONE
            // go+gle
        }

    }

/* ##################################################################################################################################### */

    // Curly brackets check
    else if (count_open_curly_bracket > 0 && count_close_curly_bracket > 0 && count_open_curly_bracket == count_close_curly_bracket) {

        if (strchr(input, '\\')) {
        
            curlyBracketsAndSlash_d_Control(input, TEXT);       // DONE
            // 1\d{10}
        }
        
        else {
            curlyBracketsControl(TEXT, input);      // DONE
            // z{3}
        }
    }

/* ##################################################################################################################################### */

    // Slash checks
    else if (strchr(input, '\\')) {

        if (strchr(input, 'n')) {
            slash_n_Control(TEXT, input);       // DONE
            // Hello\nworld
        }

        else if (strchr(input, 'd')) {
            slash_d_Control(TEXT);      // DONE
            // \d
        }

    }

/* ##################################################################################################################################### */

    // Other controls
    else if (strchr(input, '.')) {

        dotControl(TEXT, input);        // DONE
        // mi.....ft
    }

/* ##################################################################################################################################### */

    else if (strchr(input, '^')) {

        if (strchr(input, '$')) {
            powerAndDollarControl(TEXT, input);     // DONE
            // ^dog$
        }
        else {
            powerControl(TEXT, input);          // DONE
            // ^dog
        }
    }

/* ##################################################################################################################################### */

    else if (strchr(input, '$')) {
        dollarControl(TEXT, input);         // DONE
        // dog$
    }

/* ##################################################################################################################################### */

    else if ((!(strchr(input, '('))) && (!(strchr(input, ')'))) && (!(strchr(input, '['))) && (!(strchr(input, ']')))
     && (!(strchr(input, '{'))) && (!(strchr(input, '}'))) && (!(strchr(input, '^'))) && (!(strchr(input, '$'))) && (!(strchr(input, '.')))
      && (!(strchr(input, '\\'))) && (!(strchr(input, '?'))) && (!(strchr(input, '*'))) && (!(strchr(input, '+'))) && (!(strchr(input, '|')))) {

        wordControl(TEXT, input);       // DONE
        // hello
    }




/* ##################################################################################################################################### */

    return 0;
}
