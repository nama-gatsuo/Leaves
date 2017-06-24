'use strict';

var _mysql = require('mysql');

var _mysql2 = _interopRequireDefault(_mysql);

var _settings = require('./settings');

var _settings2 = _interopRequireDefault(_settings);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var NUM = 21000;
var CURRENT_NUM = 0;
var db = void 0;
var SUM = 0.0;
var COUNTRYS = [];

// db connect
db = _mysql2.default.createConnection({
    host: _settings2.default.DB_HOST,
    user: _settings2.default.DB_USER,
    password: _settings2.default.DB_PASS,
    database: _settings2.default.DB_NAME
});

init();

function init() {
    db.query('SELECT code_who,code_iso,country_name,value FROM country', function (error, results, fields) {
        if (error) throw error;

        for (var i = 0; i < results.length; i++) {
            SUM += results[i].value;
            COUNTRYS.push(results[i]);
        }
        calc();
    });
}

function calc() {
    console.log('Start');
    check();
}

function check() {

    var d = {
        country: '', city: '', age: '', sex: '', reason: '',
        lat: 0.0, lon: 0.0
    };

    var coin = Math.random() * SUM;
    var current = 0.0;
    var code_who = void 0;
    var code_iso = void 0;
    var amount = 0.0;

    for (var i = 0; i < COUNTRYS.length; i++) {
        current += COUNTRYS[i].value;
        if (coin <= current) {
            code_who = COUNTRYS[i].code_who;
            code_iso = COUNTRYS[i].code_iso;
            d.country = COUNTRYS[i].country_name;
            amount = COUNTRYS[i].value;
            break;
        } else {
            continue;
        }
    }

    code_who = code_who.toLowerCase();
    code_iso = code_iso.toLowerCase();

    coin = Math.random() * amount;

    // determin sex, age, reason
    var q = 'SELECT sex,age,ghe_code,ghe_cause,' + code_who + ' FROM country_sex_age_reason;';
    db.query(q, function (error, results, fields) {

        var cur = 0.0;

        for (var _i = 0; _i < results.length; _i++) {
            cur += results[_i][code_who];
            if (coin < cur) {
                d.sex = results[_i]['sex'];
                d.age = results[_i]['age'];
                d.reason = results[_i]['ghe_cause'];
                break;
            } else {
                continue;
            }
        }

        // determin city
        q = 'SELECT country_code,population,latitude,longitude,combined FROM cities WHERE country_code = "' + code_iso + '" ORDER BY population DESC;';
        db.query(q, function (error, results, fields) {

            var amount = 0;

            for (var _i2 = 0; _i2 < results.length; _i2++) {
                amount += results[_i2].population;
            }

            var coin = Math.random() * amount;
            var cur = 0.0;

            for (var _i3 = 0; _i3 < results.length; _i3++) {
                cur += results[_i3].population;
                if (coin < cur) {
                    d.city = results[_i3]['combined'].split(',')[0];
                    d.lat = results[_i3]['latitude'];
                    d.lon = results[_i3]['longitude'];
                    break;
                } else {
                    continue;
                }
            }

            // insert a record to the database
            q = 'INSERT INTO random_records (country,city,latitude,longitude,sex,age,reason) ';
            q += 'VALUES("' + d.country + '","' + d.city + '","' + d.lat + '","' + d.lon + '","' + d.sex + '","' + d.age + '","' + d.reason + '");';
            db.query(q, function (error, results) {
                if (error) throw error;
                console.log(CURRENT_NUM + ' records inserted');

                if (CURRENT_NUM < NUM) {
                    check();
                    CURRENT_NUM++;
                } else {
                    console.log('End');
                }
            });
        });
    });
}
//# sourceMappingURL=dataCreate.js.map
