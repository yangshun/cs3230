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

# R0 :  ['A1', 'A10', 'A2']
# R1 :  ['A7', 'A6', 'A8']
# R2 :  ['A4', 'A5', 'A3']
# R3 :  ['A9']
