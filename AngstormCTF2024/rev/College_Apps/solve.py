import re

# Load the data from the file
with open('admissions-database.txt', 'r') as f:
    data = f.read()

# Extract the names and numbers from the data
data_pairs = [x.split(':') for x in data.split() if ':' in x]

# Initialize global_flag_index
global_flag_index = 0

# Define the forbidden words
forbidden_words = "I of it then to who so and if me the which is from that through".split()

# Check the conditions for each suc_flag_index
matches = []
while global_flag_index < 256:  # assuming global_flag_index can't exceed 255
    for name, suc_flag_index in data_pairs:
        suc_flag_index = int(suc_flag_index, 8)  # Convert to octal
        suc_flag_index ^= 0x4A72B18C
        if (suc_flag_index & 0xFF000000) == 0xBC000000 and (suc_flag_index & 0xFF) == global_flag_index:
            matches.append(f"{name}:{suc_flag_index:X}")
    global_flag_index += 1  # increment global_flag_index

print("Without filter applied words:")
# Print only the words
words = [match.split(':')[0] for match in matches]
#print(' '.join(words))

# Print the second byte of suc_flag_index for each word
second_bytes = []
for match in matches:
    name, suc_flag_index = match.split(':')
    suc_flag_index = int(suc_flag_index, 16)
    second_byte = (suc_flag_index >> 8) & 0xFF
    second_bytes.append((name, second_byte))

# Fill the gaps with forbidden words
filled_words = []
current_index = 0
forbidden_index = 0
for name, index in second_bytes:
    while current_index < index:
        filled_words.append(forbidden_words[forbidden_index])
        current_index += 1
        forbidden_index = (forbidden_index + 1) % len(forbidden_words)
    filled_words.append(name)
    current_index += 1
    
# Cut off the last word
filled_words = filled_words[:-1]

print(' '.join(filled_words))