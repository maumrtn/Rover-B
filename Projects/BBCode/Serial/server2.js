//Loading modules
var http = require('http');
var fs = require('fs');
var path = require('path');
var b = require('bonescript');

console.log(b.getPlatform().bonescript);
// Create a variable for onboard LED USR1
var led = "USR1";
// Initialize the led as an OUTPUT
b.pinMode(led, b.OUTPUT);

//UART config
var UART1 = '/dev/ttyO1';
var UART4 = '/dev/ttyO4';
var options = {
   baudrate: 9200
}

// Initialize the server on port 8888
var server = http.createServer(function (req, res) {
    // requesting files
    var file = '.'+((req.url=='/')?'/index2.html':req.url);
    var fileExtension = path.extname(file);
    var contentType = 'text/html';
    // Uncomment if you want to add css to your web page
    /*
    if(fileExtension == '.css'){
        contentType = 'text/css';
    }*/
    fs.exists(file, function(exists){
        if(exists){
            fs.readFile(file, function(error, content){
                if(!error){
                    // Page found, write content
                    res.writeHead(200,{'content-type':contentType});
                    res.end(content);
                }
            })
        }
        else{
            // Page not found
            res.writeHead(404);
            res.end('Page not found');
        }
    })
}).listen(8888);
console.log("Server initialized...");

// Loading socket io module
var io = require('socket.io').listen(server);
console.log("SocketIO module loaded...");

// When communication is established
io.on('connection', function (socket) {
    socket.on('changeLED', handleChangeLED);
    socket.on('sendUART', handleSendUART);
});

// Open Serial Ports UART1 and UART4
b.serialOpen(UART1, options, onUART1);
b.serialOpen(UART4, options, onUART4);

// Change led state when a button is pressed
function handleChangeLED(data) {
    var newData = JSON.parse(data);
    console.log("LED = " + newData.state);
    // turns the LED ON or OFF
    b.digitalWrite(led, newData.state);
}

// Send data over UART when a button is pressed
function handleSendUART(data) {
    var newData = JSON.parse(data);
    
    //console.log("Input = " + newData.state);
    switch(newData.state) {
    case 1:
        Sending1;
        console.log("UART1 fired");
        break;
    case 4:
        Sending4;
        console.log("UART4 fired");
        break;
    default:
        console.log("Unknown Input. State = " + newData.state);
    }
}

function onUART1(x) {
    if (x.err) {
        console.log('_ERROR_ ' + JSON.stringify(x));
    }
    if (x.event == 'open') {
        console.log('*** UART1 OPENED ***');
    }
    if (x.event == 'data') {
        // console.log('UART1 Rx: ' + String(x.data));
        console.log('UART1 Rx: ' + x.data);
    }
}

function onUART4(x) {
    if (x.err) {
        console.log('_ERROR_ ' + JSON.stringify(x));
    }
    if (x.event == 'open') {
        console.log('*** UART4 OPENED ***');
    }
    if (x.event == 'data') {
        console.log('UART4 Rx: ' + String(x.data));
    }
}

function Sending1() {
    b.serialWrite(UART1, 'aaa');
}

function Sending4() {
    b.serialWrite(UART4, 'bbb');
}

setTimeout(Sending1, 1000);
setTimeout(Sending4, 1200);



// Displaying a console message for user feedback
server.listen(8888, console.log("Server Running ..."));
