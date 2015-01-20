CS3230 Homework Set #1
==

Name: Tay Yang Shun  
Matric No: A0073063M

### S1 

(a)

To win the maximum number of snickers bars, Steven has to guess the correct number in the least number of tries possible. 

This can be viewed as a Binary Search problem, where Steven has to search for a number among a sorted list of numbers.
Steven can adopt the Binary Search approach, by guessing the middle point of the domain of possible numbers in each guess. This strategy reduces the domain of possible numbers by half with each guess.

The time complexity of a Binary Search algorithm is O(*lg n*). With an *n* of 500, the maximum number of guesses that Steven will need is ceil(lg 500) = ceil(8.96) = 9 guesses. In the worst case, Steven will get to eat 9 snickers bars, which will be the same (18 - 9 = 9) as Ken. However, on average, Steven will get to eat more snickers bars.

(b)

(i) The terminating condition of the algorithm is to have one person left standing. This algorithm will terminate because in each phase, there is at one person guaranteed to sits down and no longer participate in the algorithm. 

The number reported in Step 5 is *n*.

*n - 1* additions will be done in all.

(ii) *n - 1* phases.

(iii) *n - 1* phases.

### S2

(a)

For the first run where the boys *{a, b, c, d}* propose, the pairing are as follows: *(a, B), (b, C), (c, A), (d, D)*.

For the second run where the girls *{A, B, C, D}* propose, the pairing are as follows: *(A, c), (B, a), (C, b), (D, d)*.

When boys propose, the result is male-optimal and female-pessimal. 
When the girls propose, the result is female-optimal and male-pessimal.

If the result is the same regardless of whether of which side proposes, then the result is both
male-optimal/female-optimal, which suggests there is only one stable matching possible.

(b)

| boys | 1st | 2nd |
|------|-----|-----|
|  a   |  A  |  B  |
|  b   |  A  |  B  |

| girls | 1st | 2nd |
|-------|-----|-----|
|   A   |  a  |  b  |
|   B   |  a  |  b  |

(c)


| boys | 1st | 2nd | 3rd |
|------|-----|-----|-----|
|  a   |  A  |  B  |  C  |
|  b   |  B  |  A  |  C  |
|  b   |  A  |  B  |  C  |

| girls | 1st | 2nd | 3rd |
|-------|-----|-----|-----|
|   A   |  b  |  c  |  a  |
|   B   |  c  |  a  |  b  |
|   C   |  a  |  b  |  c  |

The algorithm terminates when the last girl gets her first proposal.
For the other *n-1* girls, they can start with their last choice they are proposed to,
and keep getting proposed to and improve by one choice each time that happens.
For each of these proposals, a previously taken boy will become free and he can propose again.
These *n-1* girls will each receive n proposals.

Hence there are (n-1) * n + 1 = n<sup>2</sup> - n + 1 proposals in total.

### S3

(ai)

```
    0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20
----+---+---+---+---+---+---+---+---+---+---+----+----+----+----+----+----+----+----+----+----+-
R0  <---- A1 --->   <------ A10 ------->         <
R1      <---- A7 --->       <------ A6 ----->     
R2          <---- A4 --->           <------- A5 --
```

Room assignment: 
- R0: A1, A10, A2
- R1: A7, A6
- R2: A4, A5

(aii)

```
    0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20
----+---+---+---+---+---+---+---+---+---+---+----+----+----+----+----+----+----+----+----+----+-
R0  <---- A1 --->   <------ A10 ------->         <------------------ A2 ----------------->
R1      <---- A7 --->       <------ A6 ----->         <------- A8 --------> 
R2          <---- A4 --->           <------- A5 ------>         <------------ A3 ------------->
R3                                                                   <------- A9 -------->
```

Room assignment: 
- R0: A1, A10, A2
- R1: A7, A6, A8
- R2: A4, A5, A3
- R3: A9

4 rooms are required.
Yes it is optimal, because from time 15-16, there are 4 concurrent events (A2, A8, A3 and A9), hence a minimum of 4 rooms will have to be used.

(b)

Explanation of data structures

- The event points are implemented as a list, and stores tuples in the following format: `(time, event_id, type: 'start/end')`.
- `rooms` is a dictionary that maps a `rooms_id` to a list of `event_ids` assigned to that room. This is to enable O(*1*) retrieval of the list of `event_ids` assigned to the room given a `room_id`.
- `free_rooms` is a list of `room_ids` of the rooms that are currently free.
- `event_locations` is a dictionary that maps an `event_id` to the `room_id` of the room assigned to that event. This is to enable O(*1*) retrieval of a given `event_id`.

```py
def lsa(events):
  event_points = []
  rooms = {}
  free_rooms = []
  events_location = {}
  room_count = 0

  # Create a list of event points from the input. Time complexity: O(n)
  for event in events:
    event_points.append((event[1], event[0], 'start'))
    event_points.append((event[2], event[0], 'end'))
  
  # Sort the event points according to time. Time complexity: O(n lg n)
  event_points.sort(key=lambda x:x[0])

  # Scanning of the event points. Time complexity: O(n)
  for point in event_points:
    event_id = point[1]
    if point[2] == 'start':
      if len(free_rooms) == 0:
        # Create new room
        new_room_id = 'R' + str(room_count)
        rooms[new_room_id] = []
        free_rooms.append(new_room_id)
        room_count += 1
      current_room_id = free_rooms.pop(0)
      events_location[event_id] = current_room_id
      rooms[current_room_id].append(event_id)
    elif point[2] == 'end':
      room_id = events_location[event_id]
      free_rooms.append(room_id)

  # Print room assignment results
  for room_id, rooms_list in rooms.iteritems():
    print room_id, ':', rooms_list

lsa([ ('A1', 0, 3), 
      ('A2', 11, 18.9), 
      ('A3', 14, 20), 
      ('A4', 2, 5.9), 
      ('A5', 8, 11.9), 
      ('A6', 6, 10), 
      ('A7', 1, 3.9), 
      ('A8', 12, 16), 
      ('A9', 15, 19), 
      ('A10', 4, 9)])

# Results:
# R0 :  ['A1', 'A10', 'A2']
# R1 :  ['A7', 'A6', 'A8']
# R2 :  ['A4', 'A5', 'A3']
# R3 :  ['A9']
```

The bottleneck of the algorithm is in the sorting step, which makes the running time O(*n lg n*).
