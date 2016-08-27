(function ($) {
  'use strict';
  Drupal.behaviors.sharrre = {
    attach: function (context, settings) {

      var setts = jQuery.parseJSON(Drupal.settings.sharrre.setts);
      var pref = Drupal.settings.sharrre.pref;

      for (var s in setts) {
        if (setts.hasOwnProperty(s)) {
          var arr = $('.' + pref + s.toLowerCase()).get();
          for (i = 0; i < arr.length; i++) {
            var obj = arr[i];
            var sobj = setts[s];
            sobj.srv = s;
            sobj.click = function (api, options) { api.simulateClick(); api.openPopup(this.srv); };
            $(obj).sharrre(sobj);
          }
        }
      }
    }
  };
})(jQuery);
