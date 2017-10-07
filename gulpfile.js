'use strict';

var gulp = require('gulp');
var sourcemaps = require('gulp-sourcemaps');
var babel = require('gulp-babel');
var concat = require('gulp-concat');

var sass = require('gulp-sass');
var uglify = require('gulp-uglify');
var pleeease = require('gulp-pleeease');
var browserify = require('browserify');
var babelify = require('babelify');
var source = require('vinyl-source-stream');
var buffer = require('vinyl-buffer');

gulp.task('server:watch', function(){
    gulp.watch('./src/server/*.js', ['server']);
});

gulp.task('server', function(){
    gulp.src('./src/server/*.js')
        .pipe(sourcemaps.init())
        // .pipe(concat('server.js'))
        .pipe(babel({ presets: ['es2015'] }))
        .pipe(sourcemaps.write('.'))
        .pipe(gulp.dest('./server'));
});

gulp.task('client:watch', function(){
    gulp.watch('./src/client/timeline/js/*.js', ['js:timeline']);
    gulp.watch('./src/client/controller/js/*.js', ['js:controller']);
    gulp.watch('./src/client/timeline/scss/*.scss', ['sass:timeline']);
    gulp.watch('./src/client/controller/scss/*.scss', ['sass:controller']);
});

gulp.task('js:timeline', function(){
    browserify('./src/client/timeline/js/main.js', { debug: false })
        .transform(babelify.configure({
            presets: ['es2015']
        }))
        .transform('browserify-shim', { global: true })
        .bundle()
        .pipe(source('main.js'))
        .pipe(buffer())
        .pipe(uglify())
        .pipe(gulp.dest('./public/timeline/js'));
});

gulp.task('sass:timeline', function(){
    gulp.src('./src/client/timeline/scss/main.scss')
        .pipe(
            sass({outputStyle: 'compressed'})
            .on('error', sass.logError)
        )
        .pipe(pleeease({
            fallbacks: {
                autoplefixer: ['last 4 versions']
            }
        }))
        .pipe(gulp.dest('./public/timeline/css'));
});

gulp.task('js:controller', function(){
    browserify('./src/client/controller/js/main.js', { debug: false })
        .transform(babelify.configure({
            presets: ['es2015']
        }))
        .transform('browserify-shim', { global: true })
        .bundle()
        .pipe(source('main.js'))
        .pipe(buffer())
        .pipe(uglify())
        .pipe(gulp.dest('./public/controller/js'));
});

gulp.task('sass:controller', function(){
    gulp.src('./src/client/controller/scss/main.scss')
        .pipe(
            sass({outputStyle: 'compressed'})
            .on('error', sass.logError)
        )
        .pipe(pleeease({
            fallbacks: {
                autoplefixer: ['last 4 versions']
            }
        }))
        .pipe(gulp.dest('./public/controller/css'));
});

gulp.task('default', ['server:watch', 'client:watch']);
