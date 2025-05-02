//inclusion des bibliothèques nécessaires
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TAILLECHAINE 40

// On définit les emojis utilisés pour la carte
/*"\xE2\x97\xBB"*/#define EMOJI_NEIGE    " "
/*"\xF0\x9F\xAA\xA8"*/#define EMOJI_PIERRE   "O"
/*"\xF0\x9F\xAA\xA8"*/#define EMOJI_DRAPEAU  "F"
/*"\xF0\x9F\x8C\xB8"*/#define EMOJI_SAPIN    "A"
#define EMOJI_PINGOUIN        "\xF0\x9F\x90\xA7"
#define EMOJI_BONHOMMENEIGE   "\xE2\x9B\x84"
#define EMOJI_OURS            "\xF0\x9F\x90\xBB\xE2\x80\x8D\xE2\x98\x84"
#define EMOJI_SKIEUR          "\xF0\x9F\x8F\x82"
#define EMOJI_SNOWBOARDER     "\xF0\x9F\x8F\x8F"
#define EMOJI_LUGISTE         "\xF0\x9F\x9B\xB7"
