/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** GetOpt
*/


#include "getopt.h"
#include <string.h>
#include <stdio.h>

char* optarg = NULL;
int optind = 1;
int opterr = 1;
int optopt = '?';

int getopt(int argc, char* const argv[], const char* optstring) {
    static int optpos = 1;
    const char* p;

    if (optind >= argc || argv[optind][0] != '-' || argv[optind][1] == '\0') {
        return -1;
    }

    if (strcmp(argv[optind], "--") == 0) {
        optind++;
        return -1;
    }

    optopt = argv[optind][optpos];
    p = strchr(optstring, optopt);

    if (p == NULL || optopt == ':') {
        if (opterr && optstring[0] != ':') {
            fprintf(stderr, "%s: unknown option -- %c\n", argv[0], optopt);
        }
        if (argv[optind][++optpos] == '\0') {
            optind++;
            optpos = 1;
        }
        return '?';
    }

    if (p[1] == ':') {
        if (argv[optind][optpos + 1] != '\0') {
            optarg = &argv[optind][optpos + 1];
            optind++;
            optpos = 1;
        }
        else if (++optind < argc) {
            optarg = argv[optind];
            optind++;
            optpos = 1;
        }
        else {
            if (opterr && optstring[0] != ':') {
                fprintf(stderr, "%s: option requires an argument -- %c\n", argv[0], optopt);
            }
            optpos = 1;
            return (optstring[0] == ':') ? ':' : '?';
        }
    }
    else {
        if (argv[optind][++optpos] == '\0') {
            optind++;
            optpos = 1;
        }
        optarg = NULL;
    }

    return optopt;
}