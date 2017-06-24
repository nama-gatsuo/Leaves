import mysql from 'mysql'
import settings from './settings'

const NUM = 21000;
let CURRENT_NUM = 0;
let db;
let SUM = 0.0;
let COUNTRYS = [];

// db connect
db = mysql.createConnection({
    host: settings.DB_HOST,
    user: settings.DB_USER,
    password: settings.DB_PASS,
    database: settings.DB_NAME
});

init();

function init(){
    db.query('SELECT code_who,code_iso,country_name,value FROM country', (error, results, fields)=>{
        if (error) throw error;

        for (let i = 0; i < results.length; i++){
            SUM += results[i].value;
            COUNTRYS.push(results[i]);
        }
        calc();
    });
}

function calc(){
    console.log('Start');
    check();
}

function check(){

    let d = {
        country: '', city: '', age: '', sex: '', reason: '',
        lat: 0.0, lon: 0.0
    };

    let coin = Math.random() * SUM;
    let current = 0.0;
    let code_who;
    let code_iso;
    let amount = 0.0;

    for (let i = 0; i < COUNTRYS.length; i++) {
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
    let q = 'SELECT sex,age,ghe_code,ghe_cause,' + code_who + ' FROM country_sex_age_reason;';
    db.query(q, (error, results, fields)=>{

        let cur = 0.0;

        for (let i = 0; i < results.length; i++) {
            cur += results[i][code_who];
            if (coin < cur) {
                d.sex = results[i]['sex'];
                d.age = results[i]['age'];
                d.reason = results[i]['ghe_cause'];
                break;
            } else {
                continue;
            }
        }


        // determin city
        q = 'SELECT country_code,population,latitude,longitude,combined FROM cities WHERE country_code = "'+ code_iso + '" ORDER BY population DESC;';
        db.query(q, (error, results, fields)=>{

            let amount = 0;

            for (let i = 0; i < results.length; i++) {
                amount += results[i].population;
            }

            let coin = Math.random() * amount;
            let cur = 0.0;

            for (let i = 0; i < results.length; i++) {
                cur += results[i].population;
                if (coin < cur) {
                    d.city = results[i]['combined'].split(',')[0];
                    d.lat = results[i]['latitude'];
                    d.lon = results[i]['longitude'];
                    break;
                } else {
                    continue;
                }
            }

            // insert a record to the database
            q = 'INSERT INTO random_records (country,city,latitude,longitude,sex,age,reason) ';
            q += 'VALUES("' + d.country + '","' + d.city + '","' + d.lat + '","' + d.lon + '","' + d.sex + '","' + d.age + '","' + d.reason + '");';
            db.query(q, (error, results) => {
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
