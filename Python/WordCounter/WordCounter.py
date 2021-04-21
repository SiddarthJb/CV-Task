class WordCounter():
    def __init__(self):
        self.file = None

    def setFile(self,filePath):
        file = open(filePath, 'r')
        self.file = file.read()

    def tokenize(self):
        if self.file is not None:
            words = self.file.lower().split()
            words = [word.replace(",","") for word in words]
            words = [word.replace(".","") for word in words]
            return words
        else:
            return None
    
    def countWordFrequency(self,words):
        word_dict = {}
        if words is not None:
            for word in words:
                if word in word_dict:
                    word_dict[word] = word_dict[word] + 1
                else:
                    word_dict[word] = 1

            return word_dict
        else:
            return None

def main():
    counter = WordCounter()
    counter.setFile("./sample_text.txt")
    words = counter.tokenize()
    word_dict = counter.countWordFrequency(words)

    for word,count in word_dict.items():
        print('Word: ' + word + ' | count: ' + str(count))


if __name__ == '__main__':
    main()
   