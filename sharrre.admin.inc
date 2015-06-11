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
 
function sharrre_admin_form($form, &$form_state){
 $services = _sharrre_services(); 
 $settings = _sharrre_settings(); 
 $vals = _sharrre_get_settings();
 $conf_type = variable_get('sharrre_conf_type','template');
 //Configuration type
 $form['conf'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sharrre Configuration'),
    '#collapsible' => FALSE,
     );

 $form['conf']['sharrre_conf_type']=array(
    '#type' => 'radios',
    '#title' => t('Select Configuration Type'),
    '#default_value' => $conf_type,
    '#options' => array('template' => t('Template'), 'manual' => t('Manual'),'custom' => 'Custom Template'),
    '#description' => t('Select Configuration type'),
     );
     
     
 
 // Manual Configuration
   $form['manual'] = array(
    '#type' => 'fieldset',
    '#title' => t('Manual Configuration'),
    '#collapsible' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="sharrre_conf_type"]' => array('value' => 'manual'),
       ),
      ),
     );
  
  foreach($services as $service => $set){
   $targs = array('@service' => ucfirst($service));
   $pref = 'sharre_'.$service;
   
   $form['manual'][$service] = array(
    '#type' => 'fieldset',
    '#title' => t('@service Settings',$targs),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
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
    '#default_value' => _sharrre_get_sett($vals,'sharrre',$service,false),
    '#description' => t("Enable @service icon",$targs),
      '#states' => array(
      'visible' => array(':input[name="sharrre_conf_type"]' => array('value' => 'manual'),
       ),
      ),
    );
    
    $form['manual'][$service][$service.'_title'] = array(
    '#type' => 'textfield',
    '#size' => 20, 
    '#maxlength' => 64, 
    '#title' => t('Title'),
    '#default_value' => _sharrre_get_sett($vals,$service,'title', $set['title']),
    '#description' => t("Text on @service icon",$targs),
    );
  }
   foreach($settings as $prop => $desc){
    if( $prop != 'title' ){
     $form['manual'][$service][$service.'_'.$prop] = array(
                       '#type' => 'checkbox',
                       '#title' => $prop,
                       '#default_value' => _sharrre_get_sett($vals,$service,$prop,FALSE),
                       '#description' => t($desc['desc']),
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
        ':input[name="sharrre_conf_type"]' => array('value' => 'template'),
       ),
      ),
     );
    $form['template']['sharrre_template'] = array(
    '#type' => 'select',
    '#title' => t('Template'),
    '#options' => _sharrre_get_templates(),
    '#default_value' => variable_get('sharrre_template','example3'),
    '#description' => t('Select template'),
    );

 $form = system_settings_form($form);
 array_unshift($form['#submit'], 'sharrre_admin_form_submit');
 return $form;
 }
 
 /**
 * Admin Form Submit Callback
 **/
function sharrre_admin_form_submit($form,&$form_state){
 $services = _sharrre_services(); 
 $settings = array_keys(_sharrre_settings()); 
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
 $form_state['values']['sharrre_settings'] = serialize($varr);
}

 