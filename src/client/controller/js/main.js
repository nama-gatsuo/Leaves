import $ from 'jquery'

let menuStatus = {
    current: 0
};

// ----- create socket connection -----
let socket = io();

// ----- click a menu itme -----
$('.menu_item').click(e => {
    let id = $(e.currentTarget).attr('value');

    if (menuStatus.current != id) {
        $('.active').removeClass('active');
        $(e.currentTarget).addClass('active');

        socket.emit('layer', id);

        menuStatus.current = id;
    }

});

$(".menu_item[value='"+ menuStatus.current +"']").addClass('active');

// no scroll
$(window).on('touchmove.noScroll', function(e) {
    e.preventDefault();
});
