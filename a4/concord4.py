import sys
import re

class concord:

    def __init__(self, input=None, output=None):
        self.input = input
        self.all_lines = self.__get_all_lines(self.input)
        self.output = output
        #self.excl_words = get_excl_words()
        #self.index_words = get_index_words()

    def __get_all_lines(self, input):
        all_lines = []
        if(input == None):
            for each in sys.stdin:
                all_lines.append(each.strip())
        else:
            f = open(input, "r")
            lines = f.readlines()
            f.close()
            for each in lines:
                all_lines.append(each.strip())
        if(all_lines[0] == "1"):
                print("Input is version 1, concord2.py expected version 2")
                exit()
        return all_lines

    def __get_input_lines(self):
        index = self.all_lines.index("\"\"\"\"")
        input_lines = self.all_lines[index+1:]
        return input_lines

    def __get_excl_words(self):
        index = self.all_lines.index("\"\"\"\"")
        excl_words = self.all_lines[2:index]
        return excl_words

    def __get_index_words(self, lines, excl):
        index_words = []
        for each in lines:
            temp_line = each.split(" ")
            [index_words.append(each) for each in temp_line if (each not in excl)]
        return index_words

    def __output_lines(self):
        

    def full_concordance(self):
        output_lines = []
        excl_words = self.__get_excl_words()
        input_lines = self.__get_input_lines()
        index_words = self.__get_index_words(input_lines, excl_words)
        [output_lines for each in index_words]
        return ["hello", "this worked"]
        #return output_lines
