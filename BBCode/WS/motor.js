//Loading modules
const b = require('bonescript');
const SerialPort = require('serialport');

var message1 ="test1";

console.log("Starting motor.js");

//Communication from main process
process.on('message', (m) => {
	console.log("MP got message:", m);
	SendUART1();
});
//Send back to main process
process.send("im alive");

//UART config
const UART1 = '/dev/ttyO1';
const uartOptions = {
	baudRate: 115200   //no need to include for default=9600
}

//Open UART
var port1 = new SerialPort(UART1, uartOptions, function (err) {
	if (err) {
		return console.log('UART1 Open Error: ', err.message);
	}
	console.log('*** UART1 OPENED ***');
});

function SendUART1() {
    console.log('Writing message: ' + message1);
    port1.write(message1, function(err) {
        if (err) {
            return console.log('Error on write: ', err.message);
        }
        console.log('message written: ' + message1);
    });
}

// Read data that is available but keep the stream from entering "flowing mode"
/*port1.on('readable', function () {
	//var incoming = port1.read; //<-this wont work for some reason
	console.log('Port 1 Incoming Data:', port1.read.toString('hex'));
});*/

// Switches the port into "flowing mode"
port1.on('data', function (data) {
  console.log('Port 1 incoming Data:', data.toString('hex'));
});

console.log("Started motor.js");


