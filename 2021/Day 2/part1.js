const fs = require('fs')
const readLine = require('readline')

var coordX = 0, coordY = 0;

var lineReader = readLine.createInterface({
    input: fs.createReadStream('input.txt')
});

lineReader.on('line', (line) => {
    if (line.startsWith('forward'))
    {
        coordX += Number(line.split(' ')[1])
    }
    else if (line.startsWith('down'))
    {
        coordY += Number(line.split(' ')[1])
    }
    else if (line.startsWith('up'))
    {
        coordY -= Number(line.split(' ')[1])
    }
})

lineReader.on('close', () => {
    console.log(`Coordinates are ${coordX} & ${coordY} -> ${coordX*coordY}`)
})