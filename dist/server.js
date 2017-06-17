'use strict';

var _express = require('express');

var _express2 = _interopRequireDefault(_express);

var _path = require('path');

var _path2 = _interopRequireDefault(_path);

var _morgan = require('morgan');

var _morgan2 = _interopRequireDefault(_morgan);

var _http = require('http');

var _http2 = _interopRequireDefault(_http);

var _socket = require('socket.io');

var _socket2 = _interopRequireDefault(_socket);

var _settings = require('./settings');

var _settings2 = _interopRequireDefault(_settings);

var _timer = require('./timer');

var _timer2 = _interopRequireDefault(_timer);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var app = (0, _express2.default)();

app.use((0, _morgan2.default)('dev'));
app.use(_express2.default.static(_path2.default.join(__dirname, '/public')));

app.get('/', function (req, res) {
    res.sendFile(_path2.default.join(__dirname, '../', 'index.html'));
});

app.get('/about', function (req, res) {
    res.send('about this page!');
});

var port = normalizePort(_settings2.default.PORT);
app.set('port', port);

var server = _http2.default.createServer(app);

server.listen(port);
server.on('error', onError);
server.on('listening', onListening);

var io = _socket2.default.listen(server);

io.sockets.on('connection', function (socket) {
    console.log('a user connected');

    socket.on('message', function (msg) {
        console.log('message: ' + msg);
        // db.query();
        io.emmit('message', msg);
    });

    socket.on('disconnect', function () {
        concole.log('user disconnected');
    });
});

function normalizePort(val) {
    var port = parseInt(val, 10);

    if (isNaN(port)) return val;
    if (port >= 0) return port;

    return false;
};

function onError(error) {
    if (error.syscall !== 'listen') {
        throw error;
    }

    var bind = typeof port === 'string' ? 'Pipe ' + port : 'Port ' + port;

    switch (error.code) {
        case 'EACCESS':
            console.error(bind + ' requires elevated priviledges');
            process.exit(1);
            break;
        case 'EADDRINUSE':
            console.error(bind + ' is already in use');
            process.exit(1);
            break;
        default:
            throw error;
    }
};

function onListening() {
    var addr = server.address();
    var bind = typeof addr === 'string' ? 'Pipe ' + addr : 'Port ' + addr.port;

    console.log('Listening on ' + bind);
};

console.log("Server starting...");
//# sourceMappingURL=server.js.map
