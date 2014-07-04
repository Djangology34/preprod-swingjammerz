/**
 * @file
 * Custom scripts for theme.
 */
(function ($) {
  $(document).ready(function() {
    baseTotal = $('#price-total').html();
    
    $( document ).ajaxComplete(function() {
      $('html, body').animate({scrollTop: 0},800);
      
      if (Drupal.settings.sj_registration) {
        var datas = Drupal.settings.sj_registration.datas;
        
        // Active the right button(s)
        if (datas.data && !isNaN(datas.data)) {
          $('button[data-id="edit-' + datas.name + '-' + datas.data + '"').addClass('active');
        }
      } else {
        $('input[type=checkbox]').attr('checked', false);
      }
    });
    
    // Ajax Form - link type input to price
    $('#edit-type input:radio').live('click', function() {
      // Update the pricer
      if ($(this).val() === 'seul') {
        $('#price-type').html(1);
        $('#price-type').attr('title', 'Seul');
        $('#price-type').attr('data-value', 1);
      } else {
        $('#price-type').html(2);
        $('#price-type').attr('title', 'Couple');
        $('#price-type').attr('data-value', 2);
      }
      
      setTotalPrice();
    });
    
    // Ajax Form - link buttons to inputs
    $('.custom-form-buttons button').live('click', function(e) {
      e.preventDefault();
      var $button = $(this);
      
      // Update the pricer
      if ($button.attr('data-price') && $button.attr('data-name')) {
        $('#price-pass').attr('title', $button.attr('data-name'));
        $('#price-pass').attr('data-price', $button.attr('data-price'));
        $('#price-pass').html($button.attr('data-price'));
      }
      
      var active = $button.hasClass('active');
      var checkboxes = $button.attr('data-type') === 'checkboxes';
      var radios = $button.attr('data-type') === 'radios';
      
      // Check checkboxes
      if (checkboxes) {
        $('input[value="' + $button.attr('data-value') + '"]').attr('checked', !active);
      }
      
      // Uncheck all buttons on radios click and check the one clicked
      if (radios) {
        if (!$button.hasClass('active')) {
          $('.custom-form-buttons button').removeClass('active');
        }
        
        $('#' + ($button.attr('data-id'))).attr('checked', true);
      }
      
      // Add|Remove active class
      if (active && checkboxes) {
        $button.removeClass('active');
      } else if (!active){
        $button.addClass('active');
      }
      
      setTotalPrice();
    })
    
    // Tipsy gravity
    $('#registration-form-pricer span').tipsy({gravity: 'n', fade: true, live: true});
    
    /**
    * Set total price
    */
    function setTotalPrice() {
      var price = $('#price-pass').attr('data-price');
      var total = (+baseTotal + +price) * $('#price-type').attr('data-value');

      $('#price-total').html(total);
    }
  });
})(jQuery);