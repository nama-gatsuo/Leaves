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

It may run in other version of libraries or OS with small modification. Because openFrameworks and nodejs can run in multi platform.

# Installation
## 1. Database setup
### 1.1. Install MySQL
Download MySQL Community Server from [here](https://dev.mysql.com/downloads/mysql/) and install it.
### 1.2. Set MySQL password of root user (optional)
In Terminal, command below
```shell
$ mysqld --skip-grant-tables
$ mysql -u root

mysql> ALTER USER 'root'@'localhost' IDENTIFIED BY 'your password';
```
For precise explanation, read [this](https://dev.mysql.com/doc/refman/5.7/en/resetting-permissions.html).
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
    * Import cities.sql in a downloaded folder to your MySql server.
    ```sql
    CREATE TABLE cities (
        'id' int(5) unsigned NOT NULL,
        'code_who' varchar(3) DEFAULT NULL,
        'code_iso' varchar(2) DEFAULT NULL,
        'country_name' varchar(50) DEFAULT NULL,
        PRIMARY KEY ('id')
    );
    ```



## 2. Server setup
### 2.1. Node.js setup
Download latest OS or version from [here](https://nodejs.org/) and install it.

### 2.2. Install node-module
* get [nodemon](https://nodemon.io/) in global by command below.

```
$ npm install -g nodemon
```
* get node modules defined in package.json
```
$ npm install
```
### 2.3.
