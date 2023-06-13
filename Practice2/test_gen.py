import random
import string

"""
n: s.length 
m: wordList.length
k: wordList[i].length
"""

# True tests
def gen_tests(true_tests=True):
    for test in range(50):
        with open('./tests/in/input' + str(test + 1) + '.txt', 'w') as f:
            # Generate wordList
            m = random.randint(1, 1000)
            wordList = []

            for i in range(m):
                # ensure element is unique
                while True:
                    # Generate wordList[i]
                    k = random.randint(1, 20)
                    
                    res = str(''.join(random.choices(string.ascii_lowercase, k=k)))  

                    if res not in wordList:
                        break
                    
                wordList.append(res)

            # Generate "True" string
            max_length = random.randint(1, 300)
            s = ''

            while len(s) < max_length:
                s = s + wordList[random.randint(0, len(wordList) - 1)]

            if not true_tests:
                return s, m, wordList
            
            # Write result to test
            f.write(f'{s}\n')
            f.write(f'{m}\n')

            for word in wordList:
                f.write(f'{word}\n')

        with open('./tests/out/output' + str(test + 1) + '.txt', 'w') as f:
            f.write('true')


def replace_random_characters(s, num_replacements):
    length = len(s)
    for _ in range(num_replacements):
        index = random.randint(0, length - 1)
        s = s[:index] + random.choice(string.ascii_lowercase) + s[index+1:]
    return s


gen_tests(true_tests=True)

# False tests
for i in range(50, 100):
    with open('./tests/in/input' + str(i + 1) + '.txt', 'w') as f:
        s, m, wordList = gen_tests(true_tests=False)
        s = replace_random_characters(s, len(s) // 2)

        # Write result to test
        f.write(f'{s}\n')
        f.write(f'{m}\n')

        for word in wordList:
            f.write(f'{word}\n')

    with open('./tests/out/output' + str(i + 1) + '.txt', 'w') as f:
        f.write('false')
