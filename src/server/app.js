import express from 'express'
import path from 'path'
import logger from 'morgan'
import http from 'http'

import settings from './settings'

export default class App {
    constructor(){
        this.exp = express();

        this.exp.use(logger('dev'));
        this.exp.use(express.static(path.join(__dirname, '../public')));

        this.exp.get('/', (req, res) => {
            res.sendFile(path.join(__dirname, '../public', 'index.html'));
        });

        // this.get('/about', (req, res) => {
        //     res.send('about this page!');
        // });

        let port = parseInt(settings.HTTP_PORT, 10);
        this.exp.set('port', port);

        this.server = http.createServer(this.exp);

        this.server.listen(port);
        this.server.on('error', this.onError.bind(this));
        this.server.on('listening', this.onListening.bind(this));

    }

    onError(error) {
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

    }

    onListening() {
        let addr = this.server.address();
        let bind = typeof addr === 'string' ? 'Pipe ' + addr : 'Port ' + addr.port;

        console.log('Listening on ' + bind);
    }
}
