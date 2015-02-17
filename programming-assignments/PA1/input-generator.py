from random import randint

def generate(n):
  string = ''
  for i in range(n):
    string += str(randint(0, 9))
  print string

print 10
generate(500050)
generate(500050)
