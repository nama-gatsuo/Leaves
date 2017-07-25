import socketIo from 'socket.io'
import App from './app'
import Timer from './timer'

let app = new App();
let timer = new Timer(app.server);
timer.init();
