import $ from 'jquery'

const MAX_COUNT = 100;
let count = 0;
let sound;

// sound
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

// ring
let $dring = $('#ring').css({ opacity: 0.92 });
$dring.click(() => {
    console.log('start');
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

// socket
let socket = io();

socket.on('new', msg => {
    setTimeout(() => {
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


        if (sound) {
            playSound(sound);
            console.log('play');
        }

        if (count > MAX_COUNT) {
            let $items = $list.children();
            let $lastItem = $items[MAX_COUNT-1];
            $lastItem.remove();
        }
    }, Math.random() * 1000);


});
