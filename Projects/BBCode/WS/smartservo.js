//Loading modules
const b = require('bonescript');
const SerialPort = require('serialport');

var message4 ="test4";
var initmessage = "FF FF 07 FE 07 FE 00";
var init = Buffer.from('ffff07fe07fe00', 'hex');
//var init = Buffer.from('ffffe07fe000', 'hex');
//var init = new Array(0xFF, 0xFF, 0x07, 0xFE, 0x07, 0xFE, 0x00);
var ledmessage = "FF FF 0A FE 03 C0 3E 35 01 01";
var led = Buffer.from('ffff0afe03c03e350101', 'hex');
var pos1message = "FF FF 0C FE 05 32 CC 00 02 04 FD 3C";
var pos1 = Buffer.from('ffff0cfe0532cc000204fd3c', 'hex');


console.log("Starting smartservo.js");

//Communication from main process
process.on('message', (m) => {
	console.log("SSP got message:", m);
	switch(m){
		case 1:
			Send1();
			break;
		case 2:
			Send2();
			break;
		case 3:
			Send3();
			break;
		default:
			console.log("Unknown Command to send over UART4!");
	}
	//SendUART4();
});
//Send back to main process
process.send("im alive");

//UART config
const UART4 = '/dev/ttyO4';
const uartOptions = {
	baudRate: 115200   //no need to include for default=9600
}

//Open UART
var port4 = new SerialPort(UART4, uartOptions, function (err) {
	if (err) {
		return console.log('UART4 Open Error: ', err.message);
	}
	console.log('*** UART4 OPENED ***');
});

function SendUART4() {
    console.log('Writing message: ' + message4);
    port4.write(init, function(err) {
        if (err) {
            return console.log('Error on write: ', err.message);
        }
        console.log('message written: ' + message4);
    });
}

function Send1() {
    console.log('Writing message: ' + initmessage);
    port4.write(init, function(err) {
        if (err) {
            return console.log('Error on write: ', err.message);
        }
        console.log('message written: ' + initmessage);
    });
}

function Send2() {
    console.log('Writing message: ' + ledmessage);
    port4.write(led, function(err) {
        if (err) {
            return console.log('Error on write: ', err.message);
        }
        console.log('message written: ' + ledmessage);
    });
}

function Send3() {
    console.log('Writing message: ' + pos1message);
    port4.write(pos1, function(err) {
        if (err) {
            return console.log('Error on write: ', err.message);
        }
        console.log('message written: ' + pos1message);
    });
}

// Read data that is available but keep the stream from entering "flowing mode"
/*port4.on('readable', function () {
	//var incoming = port4.read; //<-this wont work for some reason
	console.log('Port 4 Incoming Data:', String(port4.read()));
});*/

// Switches the port into "flowing mode"
port4.on('data', function (data) {
  console.log('Port 4 incoming Data:', data.toString('hex'));
});

console.log("Started smartservo.js");


