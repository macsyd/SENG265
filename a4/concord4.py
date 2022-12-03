import sys
import re

#define constants
FRONT_LINE_LEN = 20
BACK_LINE_LEN = 30+1

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

    def __check_excl(self, excl, word):
        for each in excl:
            m = re.match(word, each, re.IGNORECASE)
            if m:
                return False
        return True

    def __get_index_words(self, lines, excl):
        index_words = []
        for each_line in lines:
            temp_line = each_line.split(" ")
            [index_words.append(each.upper()) for each in temp_line if self.__check_excl(excl, each)]
        index_words = set(index_words)
        index_words = list(index_words)
        index_words.sort()
        return index_words

    def __format_line(self, word, line, word_pattern):
        #output = re.sub(word_pattern, word, line)
        match = re.search(r"^(.*)" + word + "(.*)$", line, re.IGNORECASE)
        front_line = match.group(1)
        while(len(front_line) > FRONT_LINE_LEN):
            front_line = re.sub(r"^\w+ ", "", front_line)
        front_line = "".join([" "*(10+FRONT_LINE_LEN-len(front_line)-1), front_line])
        back_line = match.group(2)
        while((len(back_line)+len(word)) > BACK_LINE_LEN):
            back_line = re.sub(r" \w+$", "", back_line)
        
        output = "".join([front_line, word, back_line])
        #output = re.sub(r"", " "*num, output)
        return output

    def __output_lines(self, word, lines):
        output = []
        word_pattern = re.compile(r"\b" + re.escape(word) + r"\b", re.I)
        for each_line in lines:
            m = word_pattern.search(each_line)
            if m:
                output.append(self.__format_line(word, each_line, word_pattern))
        return output

    def full_concordance(self):
        output_lines = []
        excl_words = self.__get_excl_words()
        input_lines = self.__get_input_lines()
        index_words = self.__get_index_words(input_lines, excl_words)
        [output_lines.extend(self.__output_lines(each, input_lines)) for each in index_words]
        #print("1234567890123456789012345678901234567890123456789012345678901234567890")
        return output_lines
