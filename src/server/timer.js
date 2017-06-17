import mysql from 'mysql'
import settings from './settings'

let COUNTRYS = [];
let SUM = 0.0;
const interval = 10000;

let db = mysql.createConnection({
    host: settings.DB_HOST,
    user: settings.DB_USER,
    password: settings.DB_PASS,
    database: settings.DB_NAME
});

init();
setTimeout(() => {
    check();
}, interval);


function init() {

    db.query('SELECT * FROM country', (error, results, fields)=>{
        if (error) throw error;

        for (let i = 0; i < results.length; i++){
            SUM += results[i].value;
            COUNTRYS.push(results[i]);
        }

    });
};

function check() {

    let coin = Math.random() * SUM;
    let current = 0.0;
    let code;
    let name;
    let amount = 0.0;

    for (let i = 0; i < COUNTRYS.length; i++) {
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

    let sex;
    let age;
    let reason;
    coin = Math.random() * amount;

    db.query('SELECT sex,age,ghe_code,ghe_cause,' + code + ' FROM country_sex_age_reason;', (error, results, fields)=>{

        current = 0.0;

        for (let i = 0; i < results.length; i++) {
            current += results[i][code];
            if (coin < current) {
                sex = results[i]['sex'];
                age = results[i]['age'];
                reason = results[i]['ghe_cause'];
                break;
            } else {
                continue;
            }
        }
        console.log("SEX: " + sex);
        console.log("AGE: " + age);
        console.log("REASON: " + reason);

    });

    setTimeout(() => {
        check();
    }, interval);
};
