<?php

/**
 * @file
 * (sj_registration_config_lesson.admin.inc) Lesson Config Form for Swing Jammerz Registration Module
 */

/**
 * Lesson edition and creation Implements hook_form
 *
 * @param array $form
 * @param array $form_state
 * @param int   $id
 *
 * @return array 
 */
function sj_registration_lesson_admin_form($form, &$form_state, $id = null) {
  $lesson = null;
  $form['link'] = array(
    '#markup' => '<a href="\admin\config\sj_registration">' . t('Retour au listing des cours') .'</a>'
  );
  
  if ($id) {
    $lesson = db_select('sj_lessons', 'l')
            ->fields('l')
            ->condition('sjl_id', $id, '=')
            ->execute()
            ->fetch();
    
    $submit = t('Modifier');
  }
  
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Nom du cours'),
    '#default_value' => $lesson instanceof stdClass ? $lesson->name : null,
    '#size' => 50,
    '#maxlength' => 128,
    '#required' => true
  );
  
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description du cours'),
    '#default_value' => $lesson instanceof stdClass ? $lesson->description : null,
    '#required' => false
  );
  
  $form['event'] = array(
       '#type' => 'select',
       '#title' => t('Type de l\'évenement'),
       '#options' => array(
          'cours'       => t('Cours'),
          'stage' => t('Stage')
       ),
       '#default_value' => $lesson instanceof stdClass ? $lesson->event : null
   );
  
  $form['type'] = array(
       '#type' => 'select',
       '#title' => t('Type de cours'),
       '#options' => array(
          'couple' => t('Couple'),
          'solo' => t('Solo')
       ),
       '#default_value' => $lesson instanceof stdClass ? $lesson->type : null
   );
  
  $form['day'] = array(
       '#type' => 'select',
       '#title' => t('Jour du cours'),
       '#options'    => array(
         'lundi'    => t('Lundi'),
         'mardi'   => t('Mardi'),
         'mercredi' => t('Mercredi'),
         'jeudi'  => t('Jeudi'),
         'vendredi'    => t('Vendredi'),
         'samedi'  => t('Samedi'),
         'dimanche'    => t('Dimanche')
       ),
       '#default_value' => $lesson instanceof stdClass ? $lesson->day : null
   );

  $form['time'] = array(
    '#type' => 'textfield',
    '#title' => t('Heure du cours'),
    '#default_value' => $lesson instanceof stdClass ? $lesson->time : null,
    '#size' => 50,
    '#maxlength' => 128,
    '#required' => true
  );
  
  $form['level'] = array(
       '#type' => 'select',
       '#title' => t('Niveau du cours'),
       '#options' => array(
         'débutant'      => t('Débutant'),
         'intermédiaire' => t('Intermédiaire'),
         'avancé'        => t('Avancé')
       ),
       '#default_value' => $lesson instanceof stdClass ? $lesson->level : null
   );
  
  $places = db_select('sj_places', 'p')
        ->fields('p', array('id', 'name'))
        ->condition('p.year', get_season_year())
        ->condition('p.enabled', true)
        ->execute()
        ->fetchAll();
  
  $options = array();
  foreach ($places as $place) {
    $options[$place->id] = $place->name;
  }

  $form['place_id'] = array(
    '#type' => 'radios',
    '#title' => t("Lieu"),
    '#default_value' => $lesson instanceof stdClass ? $lesson->place_id : null,
    '#options' => $options,
    '#required' => TRUE
  );
  
  $form['max_capacity_leader'] = array(
    '#type' => 'textfield',
    '#title' => t('Nombre de places maximum cavalier'),
    '#default_value' => $lesson instanceof stdClass ? $lesson->max_capacity_leader : null,
    '#size' => 50,
    '#maxlength' => 3,
    '#required' => true
  );
  
  $form['max_capacity_follower'] = array(
    '#type' => 'textfield',
    '#title' => t('Nombre de places maximum cavalière'),
    '#default_value' => $lesson instanceof stdClass ? $lesson->max_capacity_follower : null,
    '#size' => 50,
    '#maxlength' => 3,
    '#required' => true
  );
  
  if ($id) {
    $lesson_datas = check_availability($lesson);
    
    $form['availability_leader'] = array(
      '#type' => 'textfield',
      '#title' => t('Nombre de places restantes cavalier'),
      '#default_value' => $lesson_datas['leader']['availability'],
      '#size' => 50,
      '#maxlength' => 3,
      '#disabled' => true
    );

    $form['availability_follower'] = array(
      '#type' => 'textfield',
      '#title' => t('Nombre de places restantes cavalière'),
      '#default_value' => $lesson_datas['follower']['availability'],
      '#size' => 50,
      '#maxlength' => 3,
      '#disabled' => true
    );
  }
  
  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Actif'),
    '#default_value' => $lesson instanceof stdClass ? $lesson->enabled : 1
  );
  
  $form['full'] = array(
    '#type' => 'checkbox',
    '#title' => t('Plein'),
    '#default_value' => $lesson instanceof stdClass ? $lesson->full : 0
  );
  
  $form['year'] = array(
      '#type' => 'textfield',
      '#title' => t('Année correspondant au cours'),
      '#default_value' => $lesson instanceof stdClass ? $lesson->year : null,
      '#size' => 50,
      '#maxlength' => 128,
      '#required' => true
    );
  
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => isset($submit) ? $submit : t('Créer'),
      '#submit' => array('sj_registration_lesson_admin_submit'),
  );
 
  $form['submit']['#validate'][] = 'sj_registration_lesson_admin_validate';
  $form_state['l_id'] = $id;
  
  return $form;
}

/**
 * Implements hook_validate()
 *
 * @param type $form
 * @param type $form_state 
 */
function sj_registration_lesson_admin_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['max_capacity_leader'])) {
    form_set_error('max_capacity_leader', t('Vous devez indiquer le nombre de place maximum pour les cavaliers'));
  }
  
  if (!is_numeric($form_state['values']['max_capacity_follower'])) {
    form_set_error('max_capacity_follower', t('Vous devez indiquer le nombre de place maximum pour les cavalières'));
  }
}

/**
 * Implements hook_submit()
 *
 * @param type $form
 * @param type $form_state 
 */
function sj_registration_lesson_admin_submit($form, &$form_state) {
  $values = $form_state['values'];
  
  if (!$form_state['l_id']) {
    $query = db_insert('sj_lessons');
    
    drupal_set_message(t('Cours intitulé <b>@name</b> créé', array('@name' => $values['name'])));
  } else {
    $query = db_update('sj_lessons')
            ->condition('sjl_id', $form_state['l_id'], '=');
    
    drupal_set_message(t('Cours intitulé <b>@name</b> a été mis à jour', array('@name' => $values['name'])));
  }
  $query->fields(array(
      'name' => $values['name'],
      'description' => $values['description'],
      'event' => $values['event'],
      'type' => $values['type'],
      'day' => $values['day'],
      'time' => $values['time'],
      'level' => $values['level'],
      'place_id' => $values['place_id'],
      'max_capacity_leader' => $values['max_capacity_leader'],
      'max_capacity_follower' => $values['max_capacity_follower'],
      'enabled' => $values['enabled'],
      'full' => $values['full'],
      'year' => $values['year']
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
  $lesson = db_select('sj_lessons', 'l')
          ->fields('l', array('name'))
          ->condition('sjl_id', $id)
          ->execute()
          ->fetch();
  
  if (!$lesson) {
    drupal_set_message(t("Cours non trouvé"));
    
    drupal_goto('/admin/config/sj_registration');
  }
  
  
  db_delete('sj_lessons')
        ->condition('sjl_id', $id)
        ->execute();
  
  drupal_set_message(t("Le cours intitulé <b>" . $lesson->name . "</b> a été supprimé"));
  
  drupal_goto('/admin/config/sj_registration');
}
