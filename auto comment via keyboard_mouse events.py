import keyboard
import time
import random
import string

def randomString(stringLength=8):
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(stringLength))

def shuffleString(s):
    return ''.join(random.sample(s,len(s)))

keyboard.wait('Ctrl')
print("starts now")


for i in range(1,111000):
    message =  "this is almost last comment"
    keyboard.write(message + "\n")
    print(message+"\n")
    time.sleep(random.randrange(1, 5, 1 ))