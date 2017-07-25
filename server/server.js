'use strict';

var _socket = require('socket.io');

var _socket2 = _interopRequireDefault(_socket);

var _app = require('./app');

var _app2 = _interopRequireDefault(_app);

var _timer = require('./timer');

var _timer2 = _interopRequireDefault(_timer);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var app = new _app2.default();
var timer = new _timer2.default(app.server);
timer.init();
//# sourceMappingURL=server.js.map
