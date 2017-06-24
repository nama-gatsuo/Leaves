'use strict';

var _mysql = require('mysql');

var _mysql2 = _interopRequireDefault(_mysql);

var _fs = require('fs');

var _fs2 = _interopRequireDefault(_fs);

var _settings = require('./settings');

var _settings2 = _interopRequireDefault(_settings);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var db = _mysql2.default.createConnection({
    host: _settings2.default.DB_HOST,
    user: _settings2.default.DB_USER,
    password: _settings2.default.DB_PASS,
    database: _settings2.default.DB_NAME
});

var q = 'SELECT latitude,longitude,sex FROM random_records;';
db.query(q, function (error, results, fields) {
    if (error) throw error;

    _fs2.default.writeFile('data.json', JSON.stringify(results));
});
//# sourceMappingURL=dataOutput.js.map
