<?php

/**
 * @file
 * (sj_registration_config_pricer.admin.inc) Pricer Config Form for Swing Jammerz Registration Module
 */

/**
 * Pricer edition and creation Implements hook_form
 *
 * @param array $form
 * @param array $form_state
 * @param int   $id
 *
 * @return array 
 */
function sj_registration_pricer_admin_form($form, &$form_state, $id = null) {
  $pricer = null;
  $form['link'] = array(
    '#markup' => '<a href="\admin\config\sj_registration">' . t('Retour au listing des cours') .'</a>'
  );
  
  if ($id) {
    $pricer = db_select('sj_pricer', 'p')
            ->fields('p')
            ->condition('id', $id)
            ->execute()
            ->fetch();
    
    $submit = t('Modifier');
  }
  
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description du cours'),
    '#default_value' => $pricer instanceof stdClass ? $pricer->description : null,
    '#required' => false
  );
  
  $form['nb_lessons_normal'] = array(
    '#type' => 'textfield',
    '#title' => t('Nombre de cours normal'),
    '#default_value' => $pricer instanceof stdClass ? $pricer->nb_lessons_normal : null,
    '#element_validate' => array('element_validate_number')
  );
  
  $form['nb_lessons_invitational'] = array(
    '#type' => 'textfield',
    '#title' => t('Nombre de cours invitational'),
    '#default_value' => $pricer instanceof stdClass ? $pricer->nb_lessons_invitational : null,
    '#element_validate' => array('element_validate_number')
  );
  
  $passes = db_select('sj_passes', 'p')
          ->fields('p', array('sjp_id', 'name', 'currency', 'year'))
          ->execute()
          ->fetchAll();
  
  $options = array();
  foreach ($passes as $pass) {
    $options[$pass->sjp_id] = $pass->name; 
  }
  
  $form['pass_id'] = array(
    '#type' => 'select',
    '#title' => t('Pass'),
    '#default_value' => $pricer instanceof stdClass ? $pricer->pass_id : null,
    '#options' => $options
  );
  
  $form['price'] = array(
    '#type' => 'textfield',
    '#title' => t('Prix'),
    '#default_value' => $pricer instanceof stdClass ? $pricer->price : null,
    '#element_validate' => array('element_validate_number')
  );
  
  $form['currency'] = array(
       '#type' => 'select',
       '#title' => t('Devise'),
       '#options' => array(
         'EUR' => 'EUR'
       ),
       '#default_value' => $pricer instanceof stdClass ? $pricer->currency : 'EUR'
   );
  
  $form['year'] = array(
      '#type' => 'textfield',
      '#title' => t('Année correspondant au prix'),
      '#default_value' => $pricer instanceof stdClass ? $pricer->year : null,
      '#size' => 50,
      '#maxlength' => 128,
      '#required' => true
  );
  
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => isset($submit) ? $submit : t('Créer'),
      '#submit' => array('sj_registration_pricer_admin_submit'),
  );
 
  $form_state['id'] = $id;
  
  return $form;
}

/**
 * Implements hook_submit()
 *
 * @param type $form
 * @param type $form_state 
 */
function sj_registration_pricer_admin_submit($form, &$form_state) {
  $values = $form_state['values'];
  
  if (!$form_state['id']) {
    $query = db_insert('sj_pricer');
    
    drupal_set_message(t('Prix créé'));
  } else {
    $query = db_update('sj_pricer')
            ->condition('id', $form_state['id']);
    
    drupal_set_message(t('Prix mis à jour'));
  }
  
  $query->fields(array(
            'description' => $values['description'],
            'nb_lessons_normal' => $values['nb_lessons_normal'],
            'nb_lessons_invitational' => $values['nb_lessons_invitational'],
            'pass_id' => $values['pass_id'],
            'price' => $values['price'],
            'currency' => $values['currency'],
            'year' => $values['year'],
            'created_at' => format_date(time(), 'custom', 'Y-m-d H:i:s')
        ))
        ->execute();
  
  $form_state['redirect'] = 'admin/config/sj_registration';
}

/**
 * Delete a lesson
 *
 * @param int $id 
 */
function sj_registration_lesson_admin_delete($id) {
  $pricer = db_select('sj_pricer', 'p')
          ->fields('p')
          ->condition('id', $id)
          ->execute()
          ->fetch();
  
  if (!$pricer) {
    drupal_set_message(t("Prix non trouvé"));
    
    drupal_goto('/admin/config/sj_registration');
  }
  
  
  db_delete('sj_pricer')
        ->condition('id', $id)
        ->execute();
  
  drupal_set_message(t("Le prix a été supprimé"));
  
  drupal_goto('/admin/config/sj_registration');
}
