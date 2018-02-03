//Create WebSocket Server
const WebSocket = require('ws');

const wss = new WebSocket.Server({ port: 1234 });
	console.log("Server listening on Port: 1234");

//Websocket Event Handling
wss.on('connection', function connection(ws, req) {
    const ip = req.connection.remoteAddress;
    ws.on('message', function incoming(message) {
        console.log("received: %s", message);
        ws.send('ack');
		
    });
    
        ws.send('Client connected!');
    console.log('Client connected with IP: %s', ip);
});