(function ($) {
  Drupal.behaviors.sharrre = {
    attach: function (context, settings) {
     var shphp = Drupal.settings.sharrre.shphp;
        $( '.sharrre-icons' ).each(function(i, obj){
          $( this ).sharrre({
              share: {
               googlePlus: true,
               facebook: true,
               twitter: true,
               },
               urlCurl:shphp,
               enableTracking: true,
                buttons: {
                 googlePlus: {size: 'tall', annotation:'bubble'},
                 facebook: {layout: 'box_count'},
                 twitter: {count: 'vertical'},
                 digg: {type: 'DiggMedium'},
                 delicious: {size: 'tall'}
               },
               hover: function(api, options){
                 $(api.element).find('.buttons').show();
               },
               hide: function(api, options){
                $(api.element).find('.buttons').hide();
               }
          });
        });
    }
  };
})(jQuery);
