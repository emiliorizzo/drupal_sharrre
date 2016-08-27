(function ($) {
  'use strict';
  Drupal.behaviors.sharrre = {
    attach: function (context, settings) {

      var setts = jQuery.parseJSON(Drupal.settings.sharrre.setts);
      var pref = Drupal.settings.sharrre.pref;

      function selCall(i, obj) {
        var sobj = setts[s];
        sobj.srv = s;
        sobj.click = function (api, options) { api.simulateClick(); api.openPopup(this.srv); };
        $(this).sharrre(sobj);
      }

      for (s in setts) {
        if (setts.hasOwnProperty(s)) {
          var selector = '.' + pref + s.toLowerCase();
          $(selector).each(selCall(i, obj));
        }
      }
    }
  };
})(jQuery);
