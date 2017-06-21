import socketIo from 'socket.io'
import App from './app'
import Timer from './timer'

let app = new App();
let timer = new Timer(app.server);
timer.init();

// let io = socketIo.listen(server);
//
// io.sockets.on('connection', socket => {
//     console.log('a user connected');
//
//     socket.on('disconnect', () => {
//         concole.log('a user disconnected');
//     });
// });
