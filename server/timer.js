'use strict';

Object.defineProperty(exports, "__esModule", {
    value: true
});

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

var _mysql = require('mysql');

var _mysql2 = _interopRequireDefault(_mysql);

var _ws = require('ws');

var _ws2 = _interopRequireDefault(_ws);

var _osc = require('osc');

var _osc2 = _interopRequireDefault(_osc);

var _http = require('http');

var _http2 = _interopRequireDefault(_http);

var _socket = require('socket.io');

var _socket2 = _interopRequireDefault(_socket);

var _settings = require('./settings');

var _settings2 = _interopRequireDefault(_settings);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

var Timer = function () {
    function Timer(server) {
        _classCallCheck(this, Timer);

        this.COUNTRYS = [];
        this.SUM = 0.0;
        this.interval = 40000;

        this.d = {
            country: '', city: '', age: '', sex: '', reason: '',
            lat: 0.0, lon: 0.0
        };

        this.db = _mysql2.default.createConnection({
            host: _settings2.default.DB_HOST,
            user: _settings2.default.DB_USER,
            password: _settings2.default.DB_PASS,
            database: _settings2.default.DB_NAME
        });

        this.udpPort = new _osc2.default.UDPPort({
            localAddress: "0.0.0.0",
            localPort: _settings2.default.UDP_PORT,
            metadata: true
        });

        this.udpPort.open();

        this.io = _socket2.default.listen(server);
        this.io.sockets.on('connection', function (socket) {

            console.log('a user connected');

            socket.on('disconnect', function () {
                console.log('user disconnected');
            });
        });
    }

    _createClass(Timer, [{
        key: 'init',
        value: function init() {
            var _this = this;

            this.db.query('SELECT code_who,code_iso,country_name,value FROM country', function (error, results, fields) {
                if (error) throw error;

                for (var i = 0; i < results.length; i++) {
                    _this.SUM += results[i].value;
                    _this.COUNTRYS.push(results[i]);
                }

                _this.check();
            });
        }
    }, {
        key: 'check',
        value: function check() {
            var _this2 = this;

            var coin = Math.random() * this.SUM;
            var current = 0.0;
            var code_who = void 0;
            var code_iso = void 0;
            var amount = 0.0;

            for (var i = 0; i < this.COUNTRYS.length; i++) {
                current += this.COUNTRYS[i].value;
                if (coin <= current) {
                    code_who = this.COUNTRYS[i].code_who;
                    code_iso = this.COUNTRYS[i].code_iso;
                    this.d.country = this.COUNTRYS[i].country_name;
                    amount = this.COUNTRYS[i].value;
                    break;
                } else {
                    continue;
                }
            }

            console.log("COUNTRY: " + this.d.country);

            code_who = code_who.toLowerCase();
            code_iso = code_iso.toLowerCase();

            coin = Math.random() * amount;

            // determin sex, age, reason
            this.db.query('SELECT sex,age,ghe_code,ghe_cause,' + code_who + ' FROM country_sex_age_reason;', function (error, results, fields) {

                var cur = 0.0;

                for (var _i = 0; _i < results.length; _i++) {
                    cur += results[_i][code_who];
                    if (coin < cur) {
                        _this2.d.sex = results[_i]['sex'];
                        _this2.d.age = results[_i]['age'];
                        _this2.d.reason = results[_i]['ghe_cause'];
                        break;
                    } else {
                        continue;
                    }
                }
                console.log("SEX: " + _this2.d.sex);
                console.log("AGE: " + _this2.d.age);
                console.log("REASON: " + _this2.d.reason);
            });

            // determin city
            this.db.query('SELECT country_code,population,latitude,longitude,combined FROM cities WHERE country_code = "' + code_iso + '" ORDER BY population DESC;', function (error, results, fields) {

                var amount = 0;

                for (var _i2 = 0; _i2 < results.length; _i2++) {
                    amount += results[_i2].population;
                }

                var coin = Math.random() * amount;
                var cur = 0.0;

                for (var _i3 = 0; _i3 < results.length; _i3++) {
                    cur += results[_i3].population;
                    if (coin < cur) {
                        _this2.d.city = results[_i3]['combined'].split(',')[0];
                        _this2.d.lat = results[_i3]['latitude'];
                        _this2.d.lon = results[_i3]['longitude'];
                        break;
                    } else {
                        continue;
                    }
                }
                console.log("CITY: " + _this2.d.city);
                console.log("coord: " + _this2.d.lat + ", " + _this2.d.lon);
                console.log("--");

                _this2.send();
            });

            setTimeout(function () {
                _this2.check();
            }, this.interval);
        }
    }, {
        key: 'send',
        value: function send() {

            // send to oF
            this.udpPort.send({
                address: "/",
                args: [{ type: 's', value: this.d.country }, { type: 's', value: this.d.city }, { type: 's', value: this.d.age }, { type: 's', value: this.d.sex }, { type: 's', value: this.d.reason }, { type: 'f', value: this.d.lat }, { type: 'f', value: this.d.lon }]
            }, "127.0.0.1", _settings2.default.OF_PORT);

            var msg = {
                country: this.d.country,
                city: this.d.city,
                age: this.d.age,
                sex: this.d.sex,
                reason: this.d.reason
            };
            this.io.emit('new', msg);
        }
    }]);

    return Timer;
}();

exports.default = Timer;
//# sourceMappingURL=timer.js.map