/*
 * Copyright (C) 2013 STRATO.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License v2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 021110-1307, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "crc32c.h"

void usage(void)
{
	printf("usage: btrfs-crc filename\n");
	printf("    print out the btrfs crc for \"filename\"\n");
	printf("usage: btrfs-crc filename -c crc [-s seed] [-l length]\n");
	printf("    brute force search for file names with the given crc\n");
	printf("      -s seed    the random seed (default: random)\n");
	printf("      -l length  the length of the file names (default: 10)\n");
	exit(1);
}

int main(int argc, char **argv)
{
	int c;
	unsigned long checksum = 0;
	char *str;
	char *buf;
	int length = 10;
	int seed = getpid() ^ getppid();
	int loop = 0;
	int i;

	while ((c = getopt(argc, argv, "l:c:s:h")) != -1) {
		switch (c) {
		case 'l':
			length = atol(optarg);
			break;
		case 'c':
			sscanf(optarg, "%li", &checksum);
			loop = 1;
			break;
		case 's':
			seed = atol(optarg);
			break;
		case 'h':
			usage();
		case '?':
			return 255;
		}
	}

	str = argv[optind];

	if (!loop) {
		if (optind >= argc) {
			fprintf(stderr, "not enough arguments\n");
			return 255;
		}
		printf("%12u - %s\n", crc32c(~1, str, strlen(str)), str);
		return 0;
	}

	buf = malloc(length);
	if (!buf)
		return -ENOMEM;
	srand(seed);

	while (1) {
		for (i = 0; i < length; i++)
			buf[i] = rand() % 94 + 33;
		if (crc32c(~1, buf, length) == checksum)
			printf("%12lu - %.*s\n", checksum, length, buf);
	}

	return 0;
}
