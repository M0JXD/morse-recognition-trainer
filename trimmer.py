# Simple script to trim files in the assets folder
# By default, the audio files for 'E' and 'T' from https://www.meridianoutpost.com/resources/etools/calculators/calculator-morse-code.php?
# come with a intra-word gap at the end.
# We just need an inter-letter gap, which can be acheived by trimming the file two dot lengths
# Assumes name starts with the right WPM, and uses that to calculate.

import os
from pydub import AudioSegment 

for filename in os.listdir("assets"):
    if filename.endswith(".wav"):
        # Ascertain WPM from filename
        wpm = int(filename[:2])

        # Calculate two dit amounts
        trim_amount = (60 / (50 * wpm)) * 2 * 1000 

        # Load the file
        print(filename + " is being processed...")
        track = AudioSegment.from_file("assets/" + filename)

        # Trim it
        new_clip = track[ : -trim_amount]

        # Export, just in launched directory as to not overwrite OG files automatically
        print("Exporting " + filename + "...")
        new_clip.export(filename, format="wav")
        print("Export of " + filename + "done!")

print("ALL FINISHED :)")
