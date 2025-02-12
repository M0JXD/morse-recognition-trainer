# Simple script to trim files in the assets folder
# By default, the audio files for 'E' and 'T' from https://www.meridianoutpost.com/resources/etools/calculators/calculator-morse-code.php?
# come with a intra-word gap at the end.
# I just need an inter-letter gap, which can be acheived by trimming the file two dot lengths

import os
from pydub import AudioSegment 

for filename in os.listdir("assets"):
    if filename.endswith(".wav"):
        wpm = int(filename[:2])
        print("assets/" + filename)
        track = AudioSegment.from_file("assets/" + filename)

        # Two dit amounts
        trim_amount = (60 / (50 * wpm)) * 2 * 1000 

        new_clip = track[ : -trim_amount]

        new_clip.export(filename, format="wav")
