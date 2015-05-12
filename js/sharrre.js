(function ($) {
  Drupal.behaviors.sharrre = {
    attach: function (context, settings) {
     
     var setts = jQuery.parseJSON( Drupal.settings.sharrre.setts );
     var pref = Drupal.settings.sharrre.pref;
     
      for(var  s in setts){
        $( '.'+pref+s ).each(function(i, obj){
         $( this ).sharrre(setts[s]);
        });
      }
    }
  };
})(jQuery);
