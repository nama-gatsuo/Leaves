!function e(t,n,a){function o(i,r){if(!n[i]){if(!t[i]){var u="function"==typeof require&&require;if(!r&&u)return u(i,!0);if(d)return d(i,!0);var f=new Error("Cannot find module '"+i+"'");throw f.code="MODULE_NOT_FOUND",f}var l=n[i]={exports:{}};t[i][0].call(l.exports,function(e){var n=t[i][1][e];return o(n||e)},l,l.exports,e,t,n,a)}return n[i].exports}for(var d="function"==typeof require&&require,i=0;i<a.length;i++)o(a[i]);return o}({1:[function(e,t,n){(function(e){"use strict";function t(e){var t=d.createBufferSource();t.buffer=e,t.connect(d.destination),t.start(0)}var n=function(e){return e&&e.__esModule?e:{default:e}}("undefined"!=typeof window?window.$:void 0!==e?e.$:null),a=0,o=void 0;window.AudioContext=window.AudioContext||window.webkitAudioContext;var d=new AudioContext;!function(e,t){var n=new XMLHttpRequest;n.responseType="arraybuffer",n.onreadystatechange=function(){4===n.readyState&&(0!==n.status&&200!==n.status||d.decodeAudioData(n.response,function(e){o=e}))},n.open("GET",e,!0),n.send("")}("/timeline/sound/notification.mp3");var i=(0,n.default)("#ring").css({opacity:.92});i.click(function(){t(o),i.velocity({opacity:0},{duration:500,complete:function(){i.remove()}})}),io().on("new",function(e){a++;var d=(0,n.default)("#list"),i=(0,n.default)("<li/>");i.addClass("listItem");(0,n.default)("<table/>"),(0,n.default)("<tr/>");d.prepend(i.append());var r=(0,n.default)("<div/>").text(new Date);r.addClass("time");var u=(0,n.default)("<div/>").text(e.city+", "+e.country);u.addClass("place");var f=(0,n.default)("<div/>").append((0,n.default)("<span/>").addClass("label").text("SEX: "),(0,n.default)("<span/>").text(e.sex)),l=(0,n.default)("<div/>").append((0,n.default)("<span/>").addClass("label").text("AGE: "),(0,n.default)("<span/>").text(e.age));i.append(r,u,f,l);var s=(0,n.default)("<ul/>");s.addClass("reason");for(var c=e.reason.split("/"),p=0;p<c.length;p++)if(c[p]){var v=(0,n.default)("<li/>").text(c[p]);s.append(v)}i.append((0,n.default)("<div/>").addClass("label").text("REASON: "),s),i.css({backgroundColor:"#000"}),i.velocity({backgroundColor:"#fff"},3e3),o&&t(o),a>100&&d.children()[99].remove()})}).call(this,"undefined"!=typeof global?global:"undefined"!=typeof self?self:"undefined"!=typeof window?window:{})},{}]},{},[1]);