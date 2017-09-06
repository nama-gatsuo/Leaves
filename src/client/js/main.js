import $ from 'jquery'

const MAX_COUNT = 100;
let count = 0;
let sound;
let menuStatus = {
    current: 0
};

// ----- audio buffer -----
// http://phiary.me/webaudio-api-getting-started/
window.AudioContext = window.AudioContext || window.webkitAudioContext;
let context = new AudioContext();

getAudioBuffer('/sound/notification.mp3');

function getAudioBuffer(url, fn){
    let req = new XMLHttpRequest();
    req.responseType = 'arraybuffer';

    req.onreadystatechange = () => {
        if (req.readyState === 4) {
            if (req.status === 0 || req.status === 200) {
                context.decodeAudioData(req.response, buffer => {
                    sound = buffer;
                });
            }
        }
    };

    req.open('GET', url, true);
    req.send('');
}

function playSound(buffer){
    let source = context.createBufferSource();
    source.buffer = buffer;
    source.connect(context.destination);
    source.start(0);
}

// ----- ring to start -----
let $dring = $('#ring').css({ opacity: 0.92 });
$dring.click(() => {

    playSound(sound);
    $dring.velocity({
        opacity: 0
    }, {
        duration: 500,
        complete: () => {
            $dring.remove();
        }
    });
});

// ----- create socket connection -----
let socket = io();

// ----- get a message -----
socket.on('new', msg => {

    count++;

    let $list = $('#list');

    let $item = $('<li/>');
    $item.addClass('listItem');

    let $table = $('<table/>');
    let $tr = $('<tr/>');
    $list.prepend($item.append());

    let $dt = $('<div/>').text(new Date());
    $dt.addClass('time');

    let $dc = $('<div/>').text(msg.city + ', ' + msg.country);
    $dc.addClass('place');

    let $ds = $('<div/>').append(
        $('<span/>').addClass('label').text('SEX: '),
        $('<span/>').text(msg.sex)
    );

    let $da = $('<div/>').append(
        $('<span/>').addClass('label').text('AGE: '),
        $('<span/>').text(msg.age)
    );

    $item.append($dt, $dc, $ds, $da);

    // reason
    let $ur = $('<ul/>');
    $ur.addClass('reason');

    let reasonArray = msg.reason.split('/');
    for (let i = 0; i < reasonArray.length; i++) {
        if (reasonArray[i]){
            let $lr = $('<li/>').text(reasonArray[i]);
            $ur.append($lr);
        }
    }

    $item.append(
        $('<div/>').addClass('label').text('REASON: '), $ur
    );

    $item.css({
        backgroundColor: '#000'
    });
    $item.velocity({
        backgroundColor: '#fff'
    }, 3000);


    if (sound) playSound(sound);


    if (count > MAX_COUNT) {
        let $items = $list.children();
        let $lastItem = $items[MAX_COUNT-1];
        $lastItem.remove();
    }

});

// ----- click a menu itme -----
$('.menu-item').click(e => {
    let id = $(e.currentTarget).attr('value');

    if (menuStatus.current != id) {
        $('.active').removeClass('active');
        $(e.currentTarget).addClass('active');

        socket.emit('layer', id);

        menuStatus.current = id;
    }

});

$(".menu-item[value='"+ menuStatus.current +"']").addClass('active');

socket.on('layer', msg => {
    if (menuStatus.current != msg) {

        $('.active').removeClass('active');
        $(".menu-item[value='"+ msg +"']").addClass('active');

        menuStatus.current = msg;
    }
});
