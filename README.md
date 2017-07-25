# About
An installation art work by Ayumu Nagamatsu.
It is a data visualization in purpose to think individual death by suicide and mental illness:
* not show the sum-up of numbers but each occurrence
* use metaphors aesthetically as in an installation
* real-time simulation based on statistics of WHO

[![View in  YouTube](https://img.youtube.com/vi/eW9kozN-roA/0.jpg)](https://www.youtube.com/watch?v=eW9kozN-roA)

This displays the real time simulation of mortality occurrence caused by
“Self-harm” and “Mental disorder” based on the statistics published by WHO.
Utilizing these data, it is possible to estimate interval between each occurrence
and its attribute (age, gender, location, specific reason).

# Data source
* Cause-specific mortality:  http://www.who.int/healthinfo/global_burden_disease/estimates/en/
* World city database: https://github.com/JoshSmith/worldwide-city-database

# Requirement
Development environment is
* macOS X Siera 10.12
* openFrameworks 0.9.8
* node.js v7.9.0

It may run in other version of libraries or OS with small modification. Because openFrameworks and nodejs can run in multi platform. But for node.js it is better to select exact version (v7.9.0) with version management tool such like [ndenv](https://github.com/riywo/ndenv).

# Installation
## 1. Database setup
### 1.1. Install MySQL
Download MySQL Community Server from [here](https://dev.mysql.com/downloads/mysql/) and install it.
### 1.2. Set MySQL password of root user (optional)
* When MySQL isn't active, command below in Terminal.
    ```shell
    $ mysqld --skip-grant-tables
    $ mysql -u root

    mysql> ALTER USER 'root'@'localhost' IDENTIFIED BY 'your password';
    ```
* For precise explanation, read [this](https://dev.mysql.com/doc/refman/5.7/en/resetting-permissions.html).
### 1.3. Create tables
* Create database named "suicide_stats"
    ```sql
    CREATE DATABASE suicide_stats;
    ```
* Create table named "city"
    1. Download city database from [this repository](https://github.com/JoshSmith/worldwide-city-database) and unzip it.
    2. Create table with [this query](https://github.com/JoshSmith/worldwide-city-database/blob/master/createtable.sql).
    3. Import cities.sql in a downloaded folder to your MySql server.
        ```sql
        LOAD DATA LOCAL INFILE "/absolute_path/cities.sql"
        INTO TABLE cities
        CHARACTER SET latin1
        FIELDS TERMINATED BY '\t'
        LINES TERMINATED BY '\n'
        (combined, population, country_code, region, latitude, longitude);
        ```
* Create table named "country"
    1. Create table with query below.
        ```sql
        CREATE TABLE country (
            id int(5) unsigned NOT NULL,
            code_who varchar(3) DEFAULT NULL,
            code_iso varchar(2) DEFAULT NULL,
            country_name varchar(50) DEFAULT NULL,
            value float DEFAULT NULL,
            PRIMARY KEY (id)
        );
        ```
    2. Import csv in this repository with query below.
        ```sql
        LOAD DATA LOCAL INFILE '/absolute path/Leaves/bin/data/country.csv'
        INTO TABLE country
        CHARACTER SET utf8
        FIELDS TERMINATED BY ',' ENCLOSED BY '"'
        LINES TERMINATED BY '\r\n';
        ```
* Create table named "country_sex_age_reason"
    1. Create table with query below.
        ```sql
        CREATE TABLE country_sex_age_reason (
            id int(3) unsigned NOT NULL,
            sex varchar(10) DEFAULT NULL,
            age varchar(8) DEFAULT NULL,
            ghe_code int(4) unsigned DEFAULT NULL,
            ghe_cause varchar(300) DEFAULT NULL,
            afg FLOAT, alb FLOAT, dza FLOAT, ago FLOAT, atg FLOAT, arg FLOAT,arm FLOAT,aus FLOAT,aut FLOAT,aze FLOAT,bhs FLOAT,bhr FLOAT,bgd FLOAT,brb FLOAT,blr FLOAT,bel FLOAT,blz FLOAT,ben FLOAT,btn FLOAT,bol FLOAT,bih FLOAT,bwa FLOAT,bra FLOAT,brn FLOAT,bgr FLOAT,bfa FLOAT,bdi FLOAT,khm FLOAT,cmr FLOAT,can FLOAT,cpv FLOAT,caf FLOAT,tcd FLOAT,chl FLOAT,chn FLOAT,col FLOAT,com FLOAT,cog FLOAT,cri FLOAT,civ FLOAT,hrv FLOAT,cub FLOAT,cyp FLOAT,cze FLOAT,prk FLOAT,cod FLOAT,dnk FLOAT,dji FLOAT,dom FLOAT,ecu FLOAT,egy FLOAT,slv FLOAT,gnq FLOAT,eri FLOAT,est FLOAT,eth FLOAT,fji FLOAT,fin FLOAT,fra FLOAT,gab FLOAT,gmb FLOAT,geo FLOAT,deu FLOAT,gha FLOAT,grc FLOAT,grd FLOAT,gtm FLOAT,gin FLOAT,gnb FLOAT,guy FLOAT,hti FLOAT,hnd FLOAT,hun FLOAT,isl FLOAT,ind FLOAT,idn FLOAT,irn FLOAT,irq FLOAT,irl FLOAT,isr FLOAT,ita FLOAT,jam FLOAT,jpn FLOAT,jor FLOAT,kaz FLOAT,ken FLOAT,kir FLOAT,kwt FLOAT,kgz FLOAT,lao FLOAT,lva FLOAT,lbn FLOAT,lso FLOAT,lbr FLOAT,lby FLOAT,ltu FLOAT,lux FLOAT,mdg FLOAT,mwi FLOAT,mys FLOAT,mdv FLOAT,mli FLOAT,mlt FLOAT,mrt FLOAT,mus FLOAT,mex FLOAT,fsm FLOAT,mng FLOAT,mne FLOAT,mar FLOAT,moz FLOAT,mmr FLOAT,nam FLOAT,npl FLOAT,nld FLOAT,nzl FLOAT,nic FLOAT,ner FLOAT,nga FLOAT,nor FLOAT,omn FLOAT,pak FLOAT,pan FLOAT,png FLOAT,pry FLOAT,per FLOAT,phl FLOAT,pol FLOAT,prt FLOAT,qat FLOAT,kor FLOAT,mda FLOAT,rou FLOAT,rus FLOAT,rwa FLOAT,lca FLOAT,vct FLOAT,wsm FLOAT,stp FLOAT,sau FLOAT,sen FLOAT,srb FLOAT,syc FLOAT,sle FLOAT,sgp FLOAT,svk FLOAT,svn FLOAT,slb FLOAT,som FLOAT,zaf FLOAT,ssd FLOAT,esp FLOAT,lka FLOAT,sdn FLOAT,sur FLOAT,swz FLOAT,swe FLOAT,che FLOAT,syr FLOAT,tjk FLOAT,tha FLOAT,mkd FLOAT,tls FLOAT,tgo FLOAT,ton FLOAT,tto FLOAT,tun FLOAT,tur FLOAT,tkm FLOAT,uga FLOAT,ukr FLOAT,are FLOAT,gbr FLOAT,tza FLOAT,usa FLOAT,ury FLOAT,uzb FLOAT,vut FLOAT,ven FLOAT,vnm FLOAT,yem FLOAT,zmb FLOAT,zwe FLOAT,
            PRIMARY KEY (id)
        );
        ```
    2. Import csv in this repository with query below.
        ```sql
        LOAD DATA LOCAL INFILE '/absolute path/Leaves/bin/data/country_sex_age_reason.csv'
        INTO TABLE country_sex_age_reason
        CHARACTER SET utf8
        FIELDS TERMINATED BY ',' ENCLOSED BY '"'
        LINES TERMINATED BY '\r\n';
        ```
## 2. Server setup
### 2.1. Node.js setup
Download latest version from [here](https://nodejs.org/) and install it.

### 2.2. Install node-module
* Get [nodemon](https://nodemon.io/) in global by command below.
    ```
    $ npm install -g nodemon
    ```
* Get node modules defined in package.json
    ```
    $ cd ~/your path/Leaves
    $ npm install
    ```
### 2.3. Create settings.js
* create ```settings.js``` in ```/src/server``` directory.

    ```js
    const settings = {
        HTTP_PORT: '3307',
        DB_HOST: 'localhost',
        DB_USER: 'root',
        DB_PASS: 'YOUR PASSWORD',
        DB_NAME: 'suicide_stats',
        UDP_PORT: '8031',
        OF_PORT: '8032'
    };

    export default settings;
    ```
* run gulp and build js.
    ```shell
    $ gulp
    ```
## 3. Run!
* Run this server. (Also you need to run MySQL server.)
    ```shell
    $ nodemon server/server
    ```
* Connect your smartphone or other divices in same network with pc's IP and port ```3307```.
* Run oF app in the same machine.
