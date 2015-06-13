<?php
/**
 * @file
 * Admin page callbacks for the drupal_sharrre module.
 */

/**
 * Form builder; Configure drupal_sharrre module
 *
 * @ingroup forms
 * @see system_settings_form()
 */
 
function social_sharrre_admin_form($form, &$form_state){
 $services = _social_sharrre_services(); 
 $settings = _social_sharrre_settings(); 
 $vals = _social_sharrre_get_settings();
 $conf_type = variable_get('social_sharrre_conf_type',SOCIAL_SHARRRE_CONF_TYPE);
 //Configuration type
 $form['conf'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sharrre Configuration'),
    '#collapsible' => FALSE,
     );

 $form['conf']['social_sharrre_conf_type']=array(
    '#type' => 'radios',
    '#title' => t('Select Configuration Type'),
    '#default_value' => $conf_type,
    '#options' => array('template' => t('Sharrre Template'), 'manual' => t('Manual'),'custom' => 'In theme Folder'),
    '#description' => t('Select Configuration type'),
     );
 
 // Manual Configuration
   $form['manual'] = array(
    '#type' => 'fieldset',
    '#title' => t('Manual Configuration'),
    '#collapsible' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="social_sharrre_conf_type"]' => array('value' => 'manual'),
       ),
      ),
     );
  
  foreach($services as $service => $set){
   $targs = array('@service' => ucfirst($service));
   $fs_title = ( $service == 'sharrre' ? t('Global Override Settings') : t('@service Settings',$targs) ); 
   $collap   = ( $service == 'sharrre' ? FALSE : TRUE ); 
   
   $form['manual'][$service] = array(
    '#type' => 'fieldset',
    '#title' => $fs_title,
    '#collapsible' => $collap,
    '#collapsed' => FALSE,
     '#states' => array(
      'visible' => array(
        ':input[name="'. 'sharrre_' . $service .'"]' => array('checked' => TRUE),
       ),
      ),
     );

  if( $service != 'sharrre' ){
    $form['conf']['sharrre_'.$service] = array(
    '#type' => 'checkbox',
    '#title' => t("Enable @service icon",$targs),
    '#default_value' => _social_sharrre_get_sett($vals,'sharrre',$service,false),
    '#description' => t("Enable @service icon",$targs),
      '#states' => array(
      'visible' => array(':input[name="social_sharrre_conf_type"]' => array('value' => 'manual'),
       ),
      ),
    );
    
    $form['manual'][$service][$service.'_title'] = array(
    '#type' => 'textfield',
    '#size' => 20, 
    '#maxlength' => 64, 
    '#title' => t('Title'),
    '#default_value' => _social_sharrre_get_sett($vals,$service,'title', $set['title']),
    '#description' => t("Text on @service icon",$targs),
    );
  }
   foreach($settings as $prop => $desc){
    if( $prop != 'title' ){
     $state = ($service == 'sharrre' ? NULL : array('enabled' => 
     array(':input[name="sharrre_'.$prop.'"]' => array('checked' => FALSE)),));
     
     $form['manual'][$service][$service.'_'.$prop] = array(
                       '#type' => 'checkbox',
                       '#title' => $prop,
                       '#default_value' => _social_sharrre_get_sett($vals,$service,$prop,FALSE),
                       '#description' => t($desc['desc']),
                       '#states' => $state,
                      );
    }
   }
  }
 // Template Configuration
     $form['template'] = array(
     '#type' => 'fieldset',
     '#title' => t('Select Template'),
     '#collapsible' => FALSE,
     '#states' => array(
      'visible' => array(
        ':input[name="social_sharrre_conf_type"]' => array('value' => 'template'),
       ),
      ),
     );
    $form['template']['social_sharrre_template'] = array(
    '#type' => 'select',
    '#title' => t('Template'),
    '#options' => _social_sharrre_get_templates(),
    '#default_value' => variable_get('social_sharrre_template',SOCIAL_SHARRRE_TEMPLATE),
    '#description' => t('Select template'),
    );
    
   // Custom Configuration
   $form['custom'] = array(
    '#type' => 'fieldset',
    '#title' => t('In Theme Folder Configuration'),
    '#collapsible' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="social_sharrre_conf_type"]' => array('value' => 'custom'),
       ),
      ),
     );
    
    $form['custom']['social_sharrre_custom_style_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom Style name'),
    '#default_value' => variable_get('social_sharrre_custom_style_name',_social_sharrre_def_style_name()),
    '#description' => t('Write the name of your custom style name, if blank the default value is @default',
    array('@default' => _social_sharrre_def_style_name())),
    );

 $form = system_settings_form($form);
 array_unshift($form['#submit'], 'social_sharrre_admin_form_submit');
 return $form;
 }
 
 /**
 * Admin Form Submit Callback
 **/
function social_sharrre_admin_form_submit($form,&$form_state){
 $services = _social_sharrre_services(); 
 $settings = array_keys(_social_sharrre_settings()); 
 $settings = array_merge($settings, array_keys($services));
 $varr = array();
 
  foreach( $services as $service => $set){
   foreach( $settings as $prop){
    if( isset( $form_state['values'][$service.'_'.$prop] ) ){
      $val = $form_state['values'][$service.'_'.$prop];
      if( ( $prop == 'title' ) && ( empty( $val ) ) ){
       $val = $set['title']; 
      }
     $varr[$service][$prop] = $val;
     unset( $form_state['values'][$service.'_'.$prop] );
     unset($val);
    }
   }
  }
 $form_state['values']['social_sharrre_settings'] = serialize($varr);
}

 