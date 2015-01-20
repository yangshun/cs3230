### S1 

(a)

To win the maximum number of snickers bars, Steven has to guess the correct number in the least number of tries possible. 

This can be viewed as a Binary Search problem, where Steven has to search for a number among a sorted list of numbers.
Steven can adopt the Binary Search approach, by guessing the middle point of the domain of possible numbers in each guess. This strategy reduces the domain of possible numbers by half with each guess.

The time complexity of a Binary Search algorithm is `O(lgn)`. With an `n` of 500, the maximum number of guesses that Steven will need is ceil(lg 500) = ceil(8.96) = 9 guesses. In the worst case, Steven will get to eat 9 snickers bars, which will be the same (18-9 = 9) as Ken. However, on average, Steven will get to eat more snickers bars.

(b)

(i) The terminating condition of the algorithm is to have one person left standing. This algorithm will terminate because in each phase, there is at one person guaranteed to sits down and no longer participate in the algorithm. 

The number reported in Step 5 is n.

n-1 additions will be done in all.

(ii) n-1 phases.
(iii) n-1 phases.

### S2

(a)
For the first run where the boys {a, b, c, d} propose, the pairing are as follows:
(a, B), (b, C), (c, A), (d, D)

For the second run where the girls {A, B, C, D} propose, the pairing are as follows:
(A, c), (B, a), (C, b), (D, d)

When boys propose, the result is male-optimal and female-pessimal. 
When the girls propose, the result is female-optimal and male-pessimal.

If the result is the same regardless of whether of which side proposes, then the result is both
male-optimal/female-optimal, which suggests there is only one stable matching possible.

(b)

| boys | 1st | 2nd |      | girls | 1st | 2nd |
|-------------------      |--------------------
|  a   |  A  |  B  |      |   A   |  a  |  b  |
|  b   |  A  |  B  |      |   B   |  a  |  b  |

(c)

| boys | 1st | 2nd | 3rd |      | girls | 1st | 2nd | 3rd |
|-------------------------      |--------------------------
|  a   |  A  |  B  |  C  |      |   A   |  c  |  b  |  a  |
|  b   |  A  |  B  |  C  |      |   B   |  c  |  b  |  a  |
|  b   |  A  |  B  |  C  |      |   C   |  c  |  b  |  a  |






