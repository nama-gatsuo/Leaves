import express from 'express'
import path from 'path'
import logger from 'morgan'
import mysql from 'mysql'
import http from 'http'
import socketIo from 'socket.io'

import settings from './settings'

let app = express();

app.use(logger('dev'));
app.use(express.static(path.join(__dirname, '/public')));

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, '../', 'index.html'));
});

app.get('/about', (req, res) => {
    res.send('about this page!');
});

let port = normalizePort(settings.PORT);
app.set('port', port);

let server = http.createServer(app);

let db = mysql.createConnection({
    host: settings.HOST,
    user: settings.USER,
    password: settings.DB_PASS,
    database: settings.DB_NAME
});

server.listen(port);
server.on('error', onError);
server.on('listening', onListening);

let io = socketIo.listen(server);

io.sockets.on('connection', socket => {
    console.log('a user connected');

    socket.on('message', msg => {
        console.log('message: ' + msg);
        // db.query();
        io.emmit('message', msg);
    });

    socket.on('disconnect', () => {
        concole.log('user disconnected');
    });
});

function normalizePort(val) {
    let port = parseInt(val, 10);

    if (isNaN(port)) return val;
    if (port >= 0) return port;

    return false;
};

function onError() {
    if (error.syscall !== 'listen') {
        throw error;
    }

    let bind = typeof port === 'string' ? 'Pipe ' + port : 'Port ' + port;

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
    let addr = server.address();
    let bind = typeof addr === 'string' ? 'Pipe ' + addr : 'Port ' + addr.port;

    console.log('Listening on ' + bind);
};

console.log("server starting...");
