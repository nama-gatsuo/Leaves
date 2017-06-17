'use strict';

var _mysql = require('mysql');

var _mysql2 = _interopRequireDefault(_mysql);

var _settings = require('./settings');

var _settings2 = _interopRequireDefault(_settings);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var COUNTRYS = [];
var SUM = 0.0;
var interval = 10000;

var db = _mysql2.default.createConnection({
    host: _settings2.default.DB_HOST,
    user: _settings2.default.DB_USER,
    password: _settings2.default.DB_PASS,
    database: _settings2.default.DB_NAME
});

init();
setTimeout(function () {
    check();
}, interval);

function init() {

    db.query('SELECT * FROM country', function (error, results, fields) {
        if (error) throw error;

        for (var i = 0; i < results.length; i++) {
            SUM += results[i].value;
            COUNTRYS.push(results[i]);
        }
    });
};

function check() {

    var coin = Math.random() * SUM;
    var current = 0.0;
    var code = void 0;
    var name = void 0;
    var amount = 0.0;

    for (var i = 0; i < COUNTRYS.length; i++) {
        current += COUNTRYS[i].value;
        if (coin < current) {
            code = COUNTRYS[i].country_code;
            name = COUNTRYS[i].country_name;
            amount = COUNTRYS[i].value;
            break;
        } else {
            continue;
        }
    }

    console.log("COUNTRY: " + name);

    code = code.toLowerCase();

    var sex = void 0;
    var age = void 0;
    var reason = void 0;
    coin = Math.random() * amount;

    db.query('SELECT sex,age,ghe_code,ghe_cause,' + code + ' FROM country_sex_age_reason;', function (error, results, fields) {

        current = 0.0;

        for (var _i = 0; _i < results.length; _i++) {
            current += results[_i][code];
            if (coin < current) {
                sex = results[_i]['sex'];
                age = results[_i]['age'];
                reason = results[_i]['ghe_cause'];
                break;
            } else {
                continue;
            }
        }
        console.log("SEX: " + sex);
        console.log("AGE: " + age);
        console.log("REASON: " + reason);
    });

    setTimeout(function () {
        check();
    }, interval);
};
//# sourceMappingURL=timer.js.map
