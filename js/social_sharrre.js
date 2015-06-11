(function ($) {
  Drupal.behaviors.sharrre = {
    attach: function (context, settings) {
     
     var setts = jQuery.parseJSON( Drupal.settings.sharrre.setts );
     var pref = Drupal.settings.sharrre.pref;
     
      for(var  s in setts){
        $( '.'+pref+s.toLowerCase() ).each(function(i, obj){
         var sobj = setts[s];
         sobj.srv = s;
         sobj.click = function(api, options){api.simulateClick();api.openPopup(this.srv);};
         $( this ).sharrre(sobj);
        });
      }
    }
  };
})(jQuery);
