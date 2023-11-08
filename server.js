//Loading modules
var http = require('http');
var fs = require('fs');
var path = require('path');
var b = require('bonescript');
const { exec } = require('child_process');

// Initialize the server on port 8888
var server = http.createServer(function (req, res) {
    // requesting files
    var file = '.'+((req.url=='/')?'/index.html':req.url);
    var fileExtension = path.extname(file);
    var contentType = 'text/html';

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
            res.end('Page not found!!!');
        }
    })
}).listen(8888);

// Loading socket io module
var io = require('socket.io')(server);

io.on('connection', (socket) => {
    console.log("There is a new connection!");
    socket.on('execute-command', () => {
        // Execute the command and send the output to the client
        executeCommand((stdout) => {
            socket.emit('command-output', stdout);
        });
    });
});

// Function to execute the command
function executeCommand(callback) {
    const { exec } = require('child_process');
    const commandToExecute = './TH-task';

    exec(commandToExecute, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error executing the command: ${error}`);
            callback(`Error executing the command: ${error}`);
        } else {
            callback(`${stdout}`);
        }
    });
}


// Displaying a console message for user feedback
console.log("Server Running ...");