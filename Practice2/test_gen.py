import random
import string

"""
n: s.length 
m: wordList.length
k: wordList[i].length
"""

# True tests
for test in range(50):
    with open('./tests/inp/' + str(test) + '.inp', 'w') as f:
        # Generate wordList
        m = random.randint(1, 1000)
        wordList = []

        for i in range(m):
            # Generate wordList[i]
            k = random.randint(1, 20)
            res = ''.join(random.choices(string.ascii_lowercase + string.digits, k=k))
            wordList.append(str(res))

        # Generate "True" string
        max_length = random.randint(1, 300)
        s = ''

        while len(s) < max_length:
            s = s + wordList[random.randint(0, len(wordList) - 1)]

        # Write result to test
        f.write(f'{s}\n')
        f.write(f'{m}\n')

        for word in wordList:
            f.write(f'{word}\n')

    with open('./tests/out/' + str(test) + '.out', 'w') as f:
        f.write('true')
