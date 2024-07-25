/*BSD 3-Clause License

Copyright (c) 2024, Christian Hennes

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fetch_cheat_sheet(const char *query, int full_output) {
    char command[256];
    sprintf(command, "curl -s cheat.sh/%s", query);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n");
        exit(1);
    }

    char response[4096];
    fread(response, sizeof(char), sizeof(response) - 1, fp);
    pclose(fp);

    response[sizeof(response) - 1] = '\0'; // Ensure null-terminated string

    if (full_output) {
        printf("%s", response);
    } else {
        char *tldr_part = strstr(response, "tldr:");
        if (tldr_part) {
            printf("%s", tldr_part);
        } else {
            printf("%s", response);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-f] <query>\n", argv[0]);
        return 1;
    }

    int full_output = 0;
    const char *query;

    if (strcmp(argv[1], "-f") == 0) {
        full_output = 1;
        query = argv[2];
    } else if (argc > 2 && strcmp(argv[2], "-f") == 0) {
        full_output = 1;
        query = argv[1];
    } else {
        query = argv[1];
    }

    fetch_cheat_sheet(query, full_output);

    return 0;
}

