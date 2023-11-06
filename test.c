/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 03:45:01 by pharbst           #+#    #+#             */
/*   Updated: 2023/11/02 04:08:03 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv) {
	char *str = argv[1];

	printf("strlen: %lu\n", strlen(str));
	printf("char value: %d\n", str[2]);
	write(1, &str[2], 1);
    return 0;
}