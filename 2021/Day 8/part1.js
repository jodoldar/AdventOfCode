const fs = require('fs')
const readLine = require('readline')

var iOccurrences = 0
const unique_displays = [2,4,3,7]

var lineReader = readLine.createInterface({
    input: fs.createReadStream('input.txt')
});

lineReader.on('line', (line) => {
    displays = line.split('|')[1]
    displays = displays.trim()

    all_words = displays.split(' ')
    all_words.forEach(element => {
        if (unique_displays.includes(element.length))
            iOccurrences = iOccurrences + 1
    });
})

lineReader.on('close', () => {
    console.log(`Total occurrences are ${iOccurrences}`)
})