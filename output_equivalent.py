import sys

if len(sys.argv) != 3:
	usage()
	exit(0)

file_a = open(sys.argv[1], 'r')
file_b = open(sys.argv[2], 'r')

a_lines = file_a.readlines()
b_lines = file_b.readlines()

if len(a_lines) != len(b_lines):
	print('The files have different line counts')
	exit(0)

found = False

a_set = set()

for a_line in a_lines:
    a_set.add(a_line)

for b_line in b_lines:
    if not b_line in a_set:
        print('Difference between files')
        print(f'file_b line: {b_line}')
        exit(0)

print('The files are the same')
exit(0)


def usage():
	print('Usage: python output_equivalent.py <file_a> <file_b>')

