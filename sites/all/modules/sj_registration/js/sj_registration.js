/**
 * @file
 * Custom scripts for theme.
 */
(function ($) {
  $(document).ready(function() {
    baseTotal = $('#price-total').html();
    
    $( document ).ajaxComplete(function() {
      $('html, body').animate({scrollTop: 0},800);
      
      // Check if parameters are given and if not checkboxes - avoid bug do to mutliple selection and validation
      if (Drupal.settings.sj_registration && $('input[type=checkbox]').length === 0) {
        var datas = Drupal.settings.sj_registration.datas;
        
        // Activate the selected button(s)
        if (datas && datas.data && !isNaN(datas.data)) {
          $('button[data-id="edit-' + datas.name + '-' + datas.data + '"').addClass('active');
        }
      } else if ($('#sj_registration_lessons').length) {
        $('input[type=checkbox]').removeAttr('checked');
        
        $('#price-pass').attr('title', '');
        $('#price-pass').attr('data-price', 0);
        $('#price-pass').html(0);
        setTotalPrice();
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
      
      // Update the pricer
      if ($button.attr('data-price') && $button.attr('data-name')) {
        $('#price-pass').attr('title', $button.attr('data-name'));
        $('#price-pass').attr('data-price', $button.attr('data-price'));
        $('#price-pass').html($button.attr('data-price'));
      } else if ($('#sj_registration_lessons').length) {
        var prices = Drupal.settings.sj_registration.pricer;
        var passId = Drupal.settings.sj_registration.pass_id;
        
        var countNormal = $('#sj_registration_lessons input[data-name="normal"][data-status="available"]:checked').size();
        var countInvitational = $('#sj_registration_lessons input[data-name="invitational"][data-status="available"]:checked').size();
        
        var i;
        for (i = 0; i < prices.length; i++) {
          if (+prices[i].nb_lessons_normal == countNormal && +prices[i].nb_lessons_invitational == countInvitational 
              && +prices[i].pass_id == +passId) {
            $('#price-pass').attr('title', prices[i].description);
            $('#price-pass').attr('data-price', prices[i].price);
            $('#price-pass').html(prices[i].price);
            break;
          } else {
            $('#price-pass').attr('title', '');
            $('#price-pass').attr('data-price', 0);
            $('#price-pass').html(0);
          }
        }
      }
      
      setTotalPrice();
    });
    
    // Add Paypal fees to price
    // Finally Paypal fees are not added to price
    /*$('.form-item-payment-method input:radio').live('click', function() {
      if ($('#paypal-fee')) {
        $('#paypal-fee').remove();
        setTotalPrice();
      }
      
      if ($('input[value="paypal"]').attr('checked')) {
        var paypal = Drupal.settings.sj_registration.paypal;
        var totalPrice = $('#price-total').html();
        var paypalFee = (totalPrice * paypal.paypal_percent) + paypal.paypal_fee;
        var fullPrice =  +totalPrice + +paypalFee;

        $('#price-type').after('<span id="paypal-fee" class="pointer" title="Paypal"> + ' + paypalFee + '</span>');
        $('#price-total').html(fullPrice);
      }
    });*/
    
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