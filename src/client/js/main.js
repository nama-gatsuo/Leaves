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

// socket
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

    $item.css({
        backgroundColor: '#000'
    });
    $item.velocity({
        backgroundColor: '#fff'
    }, 3000);

    $item.click(()=>{
        playSound(sound);
        console.log('play');
    });

    if (sound) {
        playSound(sound);
        console.log('play');
    }

    if (count > MAX_COUNT) {
        let $items = $list.children();
        let $lastItem = $items[MAX_COUNT-1];
        $lastItem.remove();
    }

});
