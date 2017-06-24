import mysql from 'mysql'
import fs from 'fs'

import settings from './settings'

let db = mysql.createConnection({
    host: settings.DB_HOST,
    user: settings.DB_USER,
    password: settings.DB_PASS,
    database: settings.DB_NAME
});

let q = 'SELECT latitude,longitude,sex FROM random_records;';
db.query(q, (error, results, fields)=>{
    if (error) throw error;

    fs.writeFile('data.json', JSON.stringify(results));
});
