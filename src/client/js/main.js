import $ from 'jquery'

const MAX_COUNT = 10;
let count = 0;

let socket = io();

socket.on('new', msg => {
    count++;

    let $list = $('#list');

    let $item = $('<li></li>');
    $item.addClass('listItem');

    let $dt = $('<div/>').text(new Date());
    $dt.addClass('time');

    let $dc = $('<div/>').text(msg.city + ', ' + msg.country);
    $dc.addClass('place');

    let $dd = $('<div/>').text(msg.sex + ', ' + msg.age);
    $dd.addClass('demogra');

    let $dr = $('<div/>').text(msg.reason);
    $dd.addClass('reason');

    $item.append($dt, $dc, $dd, $dr);
    $list.prepend($item);

    if (count > MAX_COUNT) {
        let $items = $list.children();
        let $lastItem = $items[MAX_COUNT-1];
        $lastItem.remove();
    }

});
