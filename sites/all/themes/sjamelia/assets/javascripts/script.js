/**
 * @file
 * Custom scripts for theme.
 */
(function ($) {
  $(document).ready(function() {
    // Main-menu links hover animation
    $('.menu-anim').hover(function() {
        if ($(window).width() > 768) {
          $(this).find('span').stop().animate({'width': '100%'}, 1000);
        }
      }, function() {
        if ($(window).width() > 768) {
          $(this).find('span').stop().animate({'width': 0}, 1000);
        }
      }
    );
      
    // Scroll to top event
    $('#back-to-top').click(function(e){
      $('html, body').animate({scrollTop: 0},800);
      return false;
    });
    
    // Fixed navbar
    var position = $('#nav-dynamic-fixed').position();
    $(window).scroll(function () {
      var y = $(this).scrollTop();
      
      if (y >= 400) {
        if ($('#nav-dynamic-fixed').css('position') === 'relative') {
          $('#nav-dynamic-fixed').css('top', position.top - 52 + 'px').css('position', 'fixed').animate({'top': position.top + 'px'}, 1000);
        }
      } else if (y <= position.top)  {
        $('#nav-dynamic-fixed').css({'position': 'relative', 'top': 0});
      }
    });
  });
})(jQuery);
