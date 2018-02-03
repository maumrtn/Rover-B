//Loading modules
const b = require('bonescript');
const WebSocket = require('ws');
const cp = require('child_process');
const exec = require('child_process').exec;

//Variable Declaration
var serverport = 8888;

//Console commands to configure pins
exec('config-pin P9.11 uart; config-pin P9.13 uart; config-pin P9.24 uart; config-pin P9.26 uart', (e, stdout, stderr)=> {
    if (e instanceof Error) {
        console.error(e);
        throw e;
    }
    console.log('stdout ', stdout);
    console.log('stderr ', stderr);
});


//Creating Peripheral Processes
const smartServoProcess = cp.fork('./smartservo.js');
	console.log("forked smartservo.js process");
const motorProcess = cp.fork('./motor.js');
	console.log("forked motor.js process");

//Create Communication Handlers for SubProcesses
smartServoProcess.on('message', (m) => {
	console.log("Message from Servos:", m);
});
motorProcess.on('message', (n) => {
	console.log("Message from Motors:", n);
});

//Create WebSocket Server
const wss = new WebSocket.Server({ port: serverport });
	console.log("Server listening on Port: %s", serverport);

//Websocket Event Handling
wss.on('connection', function connection(ws, req) {
    const ip = req.connection.remoteAddress;
    ws.on('message', function incoming(message) {
        console.log("received: %s", message);
        ws.send('ack');
		var newMessage = JSON.parse(message);
		//console.log("parsed message: "+ String(newMessage));
		
		switch(newMessage.cmd) {
		case "steer":
			//smartServoProcess.send("test subprocess connection");
			smartServoProcess.send(newMessage.data);
			console.log("Sent Message to SSP");
			break;
		case "drive":
			motorProcess.send("test subprocess connection");
			console.log("Sent Message to MP");
			break;
		default:
			console.log("Unknown Input. Message = "+ String(newMessage.cmd));
		}
    });
    
    ws.send('Client connected');
    console.log('Client connected with IP: %s', ip);
});


