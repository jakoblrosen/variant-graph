import sys

if len(sys.argv) != 2:
	usage()
	exit(0)

file = open(sys.argv[1], 'r')
lines = file.readlines()

max_variant = 0

for line in lines:
	nums = line.split(',')
	for num in nums:
		max_variant = max(max_variant, int(num))

print(max_variant)


def usage():
	print('Usage: python max_variant.py <input_file>')

