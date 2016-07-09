#! python3

import argparse
from random import randint

#start
ap = argparse.ArgumentParser()
ap.add_argument("-f", "--file", help="file(s) to create, separate each with a
                comma, like 'file1,file2,file3'", required=True)
ap.add_argument("-f", "--file", help="file to output the result")
args = vars(ap.parse_args())
#read from the file
img = cv2.imread(args['image'])


with open( , 'w') as eita:
    eita.write(''.join(['1' for _ in range(randint(500, 695)]))
    eita.write('VIRUS')

