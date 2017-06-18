import mysql from 'mysql'
import WebSocket from 'ws'
import osc from 'osc'
import http from 'http'

import settings from './settings'

export default class Timer {
    constructor(){

        this.COUNTRYS = [];
        this.SUM = 0.0;
        this.interval = 40000;

        this.d = {
            country: '', city: '', age: '', sex: '', reason: '',
            lat: 0.0, lon: 0.0
        };

        this.db = mysql.createConnection({
            host: settings.DB_HOST,
            user: settings.DB_USER,
            password: settings.DB_PASS,
            database: settings.DB_NAME
        });

        this.udpPort = new osc.UDPPort({
            localAddress: "0.0.0.0",
            localPort: settings.UDP_PORT,
            metadata: true
        });

        this.udpPort.open();
    }

    init(){
        this.db.query('SELECT code_who,code_iso,country_name,value FROM country', (error, results, fields)=>{
            if (error) throw error;

            for (let i = 0; i < results.length; i++){
                this.SUM += results[i].value;
                this.COUNTRYS.push(results[i]);
            }

            this.check();
        });
    }

    check(){

        let coin = Math.random() * this.SUM;
        let current = 0.0;
        let code_who;
        let code_iso;
        let amount = 0.0;

        for (let i = 0; i < this.COUNTRYS.length; i++) {
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
        this.db.query('SELECT sex,age,ghe_code,ghe_cause,' + code_who + ' FROM country_sex_age_reason;', (error, results, fields)=>{

            let cur = 0.0;

            for (let i = 0; i < results.length; i++) {
                cur += results[i][code_who];
                if (coin < cur) {
                    this.d.sex = results[i]['sex'];
                    this.d.age = results[i]['age'];
                    this.d.reason = results[i]['ghe_cause'];
                    break;
                } else {
                    continue;
                }
            }
            console.log("SEX: " + this.d.sex);
            console.log("AGE: " + this.d.age);
            console.log("REASON: " + this.d.reason);
        });

        // determin city
        this.db.query(
            'SELECT country_code,population,latitude,longitude,combined FROM cities WHERE country_code = "'+ code_iso + '" ORDER BY population DESC;',
            (error, results, fields)=>{

                let amount = 0;

                for (let i = 0; i < results.length; i++) {
                    amount += results[i].population;
                }

                let coin = Math.random() * amount;
                let cur = 0.0;

                for (let i = 0; i < results.length; i++) {
                    cur += results[i].population;
                    if (coin < cur) {
                        this.d.city = results[i]['combined'].split(',')[0];
                        this.d.lat = results[i]['latitude'];
                        this.d.lon = results[i]['longitude'];
                        break;
                    } else {
                        continue;
                    }
                }
                console.log("CITY: " + this.d.city);
                console.log("coord: " + this.d.lat + ", " + this.d.lon);
                console.log("--");

                this.send();
            }
        );

        setTimeout(() => {
            this.check();
        }, this.interval);
    }

    send(){

        // send to oF
        this.udpPort.send({
            address: "/",
            args: [
                { type: 's', value: this.d.country },
                { type: 's', value: this.d.city },
                { type: 's', value: this.d.age },
                { type: 's', value: this.d.sex },
                { type: 's', value: this.d.reason },
                { type: 'f', value: this.d.lat },
                { type: 'f', value: this.d.lon }
            ]
        }, "127.0.0.1", settings.OF_PORT);

    }
}
