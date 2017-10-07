'use strict';

Object.defineProperty(exports, "__esModule", {
    value: true
});

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

var _express = require('express');

var _express2 = _interopRequireDefault(_express);

var _path = require('path');

var _path2 = _interopRequireDefault(_path);

var _morgan = require('morgan');

var _morgan2 = _interopRequireDefault(_morgan);

var _http = require('http');

var _http2 = _interopRequireDefault(_http);

var _settings = require('./settings');

var _settings2 = _interopRequireDefault(_settings);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

var App = function () {
    function App() {
        _classCallCheck(this, App);

        this.exp = (0, _express2.default)();

        this.exp.use((0, _morgan2.default)('dev'));
        this.exp.use(_express2.default.static(_path2.default.join(__dirname, '../public')));

        this.exp.get('/timeline', function (req, res) {
            res.sendFile(_path2.default.join(__dirname, '../public', 'timeline/index.html'));
        });
        this.exp.get('/controller', function (req, res) {
            res.sendFile(_path2.default.join(__dirname, '../public', 'controller/index.html'));
        });

        var port = parseInt(_settings2.default.HTTP_PORT, 10);
        this.exp.set('port', port);

        this.server = _http2.default.createServer(this.exp);

        this.server.listen(port);
        this.server.on('error', this.onError.bind(this));
        this.server.on('listening', this.onListening.bind(this));
    }

    _createClass(App, [{
        key: 'onError',
        value: function onError(error) {
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
        }
    }, {
        key: 'onListening',
        value: function onListening() {
            var addr = this.server.address();
            var bind = typeof addr === 'string' ? 'Pipe ' + addr : 'Port ' + addr.port;

            console.log('Listening on ' + bind);
        }
    }]);

    return App;
}();

exports.default = App;
//# sourceMappingURL=app.js.map
