# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/23 13:41:35 by votre_login       #+#    #+#              #
#    Updated: 2026/02/23 21:34:17 by votre_login      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import random
import subprocess

def main():
    n = 3000
    sequence = [random.randint(1, 10000) for _ in range(n)]

    input = [str(n) for n in sequence]
    commande = ["./PmergeMe"] + input
    output = subprocess.run(commande, capture_output=True, text=True)

    lines = output.stdout.strip().split('\n')
    line_vector = lines[-3]
    line_deque = lines[-2]

    vector_time = int(''.join(filter(str.isdigit, line_vector.split()[-1])))
    deque_time = int(''.join(filter(str.isdigit, line_deque.split()[-1])))

    print(vector_time)
    print(deque_time)

if __name__ == "__main__":
    main()
