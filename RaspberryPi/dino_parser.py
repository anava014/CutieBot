# import requests
# import RPi.GPIO as GPIO


# command_byte = requests.get('http://dinorobotics.net/requests.txt');
command_byte = 63

#NO!!! testBit() returns a nonzero result, 2**offset, if the bit at 'offset' is one.
#testBit() returns 1 if there is a 1 at offset bit, 0 if there is a 0 at offset bit

def testBit(int_type, offset):
  mask = 1 << offset
  #return(int_type & mask)
  if (int_type & mask) != 0: return True
  return False

""" DON'T NEED THESE FUNCTIONS BUT COOL
# setBit() returns an integer with the bit at 'offset' set to 1.

def setBit(int_type, offset):
  mask = 1 << offset
  return(int_type | mask)

# clearBit() returns an integer with the bit at 'offset' cleared.

def clearBit(int_type, offset):
  mask = ~(1 << offset)
  return(int_type & mask)

# toggleBit() returns an integer with the bit at 'offset' inverted, 0 -> 1 and 1 -> 0.

def toggleBit(int_type, offset):
  mask = 1 << offset
  return(int_type ^ mask)
"""

""" TEST CODE
one = 1
two = 2
three = 3
four = 4
eight = 8


# print(testBit(one,0));
# print(testBit(two,1));
# print(testBit(four,2));
# print(testBit(eight,3));

# print(testBit(four,0))
# print(testBit(four,1))
# print(testBit(four,2))
# print(testBit(four,3))

"""

def getA():
  return testBit(command_byte,0)

def getB():
  return testBit(command_byte,1)

def getSel():
  return testBit(command_byte,2)

def getStart():
  return testBit(command_byte,3)

def getUp():
  return testBit(command_byte,4)

def getDown():
  return testBit(command_byte,5)

def getLeft():
  return testBit(command_byte,6)

def getRight():
  return testBit(command_byte,7)

""" STATE MACHINES """

def Camera_SM():
  if getA()==True : print("SHOOT")
  elif getB()==True : print("DANCE")
  return

def Menu_SM():
  if getSel()==True : print("MENU")
  elif getStart()==True : print("MENU")
  return

def Movement_SM():
  if getUp()==True : print("UP")
  elif getDown()==True : print("DOWN")
  elif getLeft()==True : print("LEFT")
  elif getRight()==True : print("RIGHT")
  return


""" LOOP """
while 1:
  Menu_SM()
  Movement_SM()
  Camera_SM
