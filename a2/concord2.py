#!/usr/bin/env python3

import sys

#Checks each word in the line, if it is not an exclusion word,
#it is added to a list of words to index
def check_excl(line, excl_words):
	index_words = []
	if(line == ""):
		return index_words
	temp = line.split(" ")
	for each_word in temp:
		is_excl = False
		for excl_word in excl_words:
			if(each_word.upper() == excl_word.upper()):
				is_excl = True
				break
		if(not is_excl):
			index_words.append(each_word.lower())
	
	return index_words

#Formats the beginning of the output string with correct spacing
def format_front_line(line):
	front_line = ""
	index = 30
	for i in range(len(line)-1, 0-1, -1):
		if((index - 1 - len(line[i])) >= 10):
			front_line = " ".join([line[i], front_line])
			index -= len(line[i]) + 1
		else:
			break
	if(index > 10):
		front_line = "".join([" "*(index-10), front_line])
	
	return front_line

#Prints the formatted line
def print_line(line, index):
	line[index] = line[index].upper()
	
	front_line = " "*9 + format_front_line(line[:index])
	output_line = "".join([front_line, line[index]])
	ind = 30 + len(line[index])
	
	for i in range(index+1, len(line)):
		if((len(line[i]) + 1 + ind) <= 61):
			#add to output
			output_line = " ".join([output_line, line[i]])
			ind += 1 + len(line[i])
		else:
			break
	output_line = output_line.rstrip()
	print(output_line)

#Searches each line for the index word, if found, it outputs the formatted line
def find_indexes(index_word, index_lines):
	for each_line in index_lines:
		line = each_line.split(" ")
		temp_line = each_line.lower()
		temp_line = temp_line.split(" ")
		for each_word in temp_line:
			if(each_word == index_word):
				print_line(line, temp_line.index(index_word))
		

def main():
	all_input = []
	excl_words = []
	index_lines = []
	words_to_index = []
	
	#read in input
	for each_line in sys.stdin:
		line = each_line.strip()
		all_input.append(line)
	
	if(all_input[0] == "1"):
		print("Input is version 1, concord2.py expected version 2")
		exit()
	
	divider = all_input.index("\"\"\"\"")
	excl_words = all_input[2:divider]
	index_lines = all_input[divider+1:]
	
	#find words to index
	for each in index_lines:
		words_to_index.extend(check_excl(each, excl_words))
	
	#sort list of index words & remove duplicates
	words_to_index = set(words_to_index)
	words_to_index = list(words_to_index)
	words_to_index.sort()
	
	#output each index word in the line it is found in
	for each_word in words_to_index:
		find_indexes(each_word, index_lines)


if __name__ == "__main__":
	main()
