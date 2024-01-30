/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 22:36:06 by irgonzal          #+#    #+#             */
/*   Updated: 2024/01/30 22:31:44 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *say_hello(void *arg)
{
    pthread_mutex_lock(arg);
    sleep(3);
    printf("Hello\n");
    if (!arg)
        printf("Bye...\n");
    pthread_mutex_unlock(arg);
    return (NULL);
}

int    create_philosophers(char **argv)
{
    pthread_t       *philosophers;
    int             i;
    int             n;
    int             ret;
    pthread_mutex_t lock;
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("Mutex initialization failed.\n");
        return (1);
    }
    n = atoi(argv[1]);
    philosophers = malloc(n * sizeof(pthread_t));
    if (!philosophers)
        return (1);
    i = 0;
    while (i < n)
    {
        printf("Creating %d\n", i);
        ret = pthread_create(&philosophers[i], NULL, say_hello, &lock);
        if (ret != 0)
            printf("Fail\n");
        i++;
    }
    while (i >= 0)
    {
        pthread_join(philosophers[i], NULL);
        i--;
    }
    free(philosophers);
    pthread_mutex_destroy(&lock);
    return (0);
    
}

int	main(int argc, char **argv)
{
	if (validate(argc, argv) != 0)
		exit(1);
    create_philosophers(argv);
    exit(0);
}
/*
- Idea: estructura con la información de argv
- Los filosofos son estructuras o directamente hilos?

*/