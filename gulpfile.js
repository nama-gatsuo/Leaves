'use strict';

var gulp = require('gulp');
var sourcemaps = require('gulp-sourcemaps');
var babel = require('gulp-babel');
var concat = require('gulp-concat');

gulp.task('server:watch', function(){
    gulp.watch('./src/server/*.js', ['server']);
});

gulp.task('server', function(){
    gulp.src('./src/server/*.js')
        .pipe(sourcemaps.init())
        // .pipe(concat('server.js'))
        .pipe(babel({ presets: ['es2015'] }))
        .pipe(sourcemaps.write('.'))
        .pipe(gulp.dest('./dist'));
});

gulp.task('default', ['server:watch']);
