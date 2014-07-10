<?php

/**
 * @file
 * (sj_registration_config.admin.inc) Config Form for Swing Jammerz Registration
 */

/**
 * Display tables in admin
 *
 * @return array 
 */
function sj_registration_admin()
{
  drupal_add_js('misc/form.js');
  drupal_add_js('misc/collapse.js');
  drupal_add_library('system', 'drupal.collapse');
  
  $content = '<h1 class="center">Interface d\'admninistration des cours</h1><br/>';
  
  $content .= '<a href="/admin/config/sj_registration/stage">' . t('Aller à la page des stages') . '</a><br/><br/>';
  
  $content .= 'Année actuelle: <b>' . get_season_year()
          . '</b> - <a href="/admin/config/sj_registration/season/edit">' . t('Modifier') . '</a><br/>';
  
  $content .= 'Année de filtrage: <b>' . get_filter_year()
          . '</b> - <a href="/admin/config/sj_registration/filter/edit">' . t('Modifier') . '</a><br/>';
  
  $content .= 'Devise: <b>' . get_currency() . '</b>'
          . ' - <a href="/admin/config/sj_registration/currency/edit">' . t('Modifier') . '</a><br/>';
  
  $content .= 'Prix de l\'adhésion: <b>' . get_registration_fee() . ' ' . get_currency(true)
          . '</b> - <a href="/admin/config/sj_registration/registration_fee/edit">' . t('Modifier') . '</a><br/>';
  
  $content .= 'Inscription: <b>' . get_registration_settings(true) . '</b>'
          . ' - <a href="/admin/config/sj_registration/settings/edit">' . t('Modifier') . '</a><br/>'
          . 'Paiement en ligne: <b>' . get_registration_payment(true) . '</b>'
          . ' - <a href="/admin/config/sj_registration/settings/edit">' . t('Modifier') . '</a><br/>';
  
  $content .= render_places();
  $content .= render_passes();
  $content .= render_lessons();
  $content .= render_students();
  $content .= render_students_per_lessons();
  
  $output = array(
    'registration_admin' => array(
      '#type' => 'markup',
      '#markup' => $content,
    ),
  );
  
  return $output;
}

/**
 * Display tables in admin for stages
 *
 * @return array 
 */
function sj_registration_admin_stage()
{
  drupal_add_js('misc/form.js');
  drupal_add_js('misc/collapse.js');
  drupal_add_library('system', 'drupal.collapse');
  
  $content = '<h1 class="center">Interface d\'admninistration des stages</h1><br/>';
  
  $content .= '<a href="/admin/config/sj_registration">' . t('Aller à la page des cours') . '</a><br/>';
  
  $content .= 'Année actuelle: <b>' . variable_get('sj_registration_season_year', null)
          . '</b> - <a href="/admin/config/sj_registration/season/edit">' . t('Modifier') . '</a><br/>';
  
  $content .= 'Année de filtrage: <b>' . variable_get('sj_registration_filter_year', null)
          . '</b> - <a href="/admin/config/sj_registration/filter/edit">' . t('Modifier') . '</a><br/>';
  
  $content .= render_lessons('stage');
  $content .= render_students('stage');
  $content .= render_students_per_lessons('stage');
  
  $output = array(
    'registration_admin' => array(
      '#type' => 'markup',
      '#markup' => $content,
    ),
  );
  
  return $output;
}

/**
 * Render passes table for admin
 *
 * @return string 
 */
function render_passes() {
  $passes = db_select('sj_passes', 'p')
              ->fields('p')
              ->condition('p.year', get_filter_year())
              ->execute()
              ->fetchAll();
  
  $content = '<fieldset class="collapsible collapsed">';
  $content .= '<legend><span class="fieldset-legend">' . t('Tableau des pass') . '</span></legend>';
  
  $content .= '<div class="fieldset-wrapper">';
  $content .= '<table><thead><tr>'
          . '<th>#</th>'
          . '<th>' . t('Nom') . '</th>'
          . '<th>' . t('Prix') . '</th>'
          . '<th>' . t('Devise') . '</th>'
          . '<th>' . t('Année') . '</th>'
          . '<th>' . t('Nb de cours') . '</th>'
          . '<th class="center">' . t('Actif') . '</th>'
          . '<th class="center">' . t('Editer') . '</th>'
          . '<th class="center">' . t('Supprimer') . '</th>'
          . '</tr></thead><tbody>';
  
  foreach($passes as $pass) {
    $enabled_icon = $pass->enabled ? 'success.png' : 'stop.png';
    
    $content .= '<tr>'
            . '<td>' . $pass->sjp_id . '</td>'
            . '<td>' . $pass->name . '</td>'
            . '<td>' . $pass->price . '</td>'
            . '<td>' . $pass->currency . '</td>'
            . '<td>' . $pass->year . '</td>'
            . '<td>' . $pass->nb_lessons . '</td>'
            . '<td class="center"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/' . $enabled_icon . '" /></td>'
            . '<td class="center"><a href="/admin/config/sj_registration/pass/edit/' . $pass->sjp_id . '"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/settings.png" /></a></td>'
            . '<td class="center"><a href="/admin/config/sj_registration/pass/delete/' . $pass->sjp_id . '"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/stop.png" /></a></td>'
            . '</tr>';
  }
  
  $content .='</tbody></table>';
  $content .= '<a href="/admin/config/sj_registration/pass/new">'
    . t('Créer un nouveau pass')
    . '</a><br/><br/>';
  
  $content .= '</div></fieldset>';
  
  return $content;
}

/**
 * Render lessons table for admin
 *
 * @param string $event
 * 
 * @return string 
 */
function render_lessons($event = 'cours') {
  $lessons = db_select('sj_lessons', 'l')
          ->fields('l')
          ->condition('l.year', get_filter_year())
          ->condition('l.event', $event)
          ->execute()
          ->fetchAll();
  
  $content = '<fieldset class="collapsible collapsed">';
  $content .= '<legend><span class="fieldset-legend">' . t('Tableau des cours') . '</span></legend>';
  
  $content .= '<div class="fieldset-wrapper">';
  $content .= '<table><thead><tr>'
          . '<th>#</th>'
          . '<th>' . t('Nom') . '</th>'
          . '<th>' . t('Description') . '</th>'
          . '<th>' . t('Type') . '</th>'
          . '<th>' . t('Jour') . '</th>'
          . '<th>' . t('Heure') . '</th>'
          . '<th>' . t('Niveau') . '</th>'
          . '<th>' . t('Lieu') . '</th>'
          . '<th>' . t('Frais d\'adhésion') . '</th>'
          . '<th>' . t('Places max cavalier') . '</th>'
          . '<th>' . t('Places max cavalière') . '</th>'
          . '<th>' . t('Places restantes cavalier') . '</th>'
          . '<th>' . t('Places restantes cavalière') . '</th>'
          . '<th>' . t('Année') . '</th>'
          . '<th class="center">' . t('Plein') . '</th>'
          . '<th class="center">' . t('Actif') . '</th>'
          . '<th class="center">' . t('Editer') . '</th>'
          . '<th class="center">' . t('Supprimer') . '</th>'
          . '</tr></thead><tbody>';
  
  foreach($lessons as $lesson) {
    $enabled_icon = $lesson->enabled ? 'success.png' : 'stop.png';
    $full_icon = !$lesson->full ? 'success.png' : 'stop.png';
    
    $leader = check_availability($lesson);
    $lesson_datas = check_availability($lesson);
    
    $place = db_select('sj_places', 'p')
            ->fields('p', array('name'))
            ->condition('p.id', $lesson->place_id)
            ->condition('p.year', get_filter_year())
            ->condition('p.enabled', true)
            ->execute()
            ->fetch();
    
    $lesson_fee = $lesson->fee ? $lesson->fee : '0';
    
    $content .= '<tr>'
            . '<td>' . $lesson->sjl_id . '</td>'
            . '<td>' . $lesson->name . '</td>'
            . '<td>' . $lesson->description . '</td>'
            . '<td>' . $lesson->type . '</td>'
            . '<td>' . $lesson->day . '</td>'
            . '<td>' . $lesson->time . '</td>'
            . '<td>' . $lesson->level . '</td>'
            . '<td>' . $place->name . '</td>'
            . '<td>' . $lesson_fee . ' ' . get_currency(true) . '</td>'
            . '<td>' . $lesson->max_capacity_leader . '</td>'
            . '<td>' . $lesson->max_capacity_follower . '</td>'
            . '<td><span class="tipsy underlined pointer" title="nb d\'inscrits: ' . $lesson_datas['leader']['count'] . ' - paiement par cheque: ' . $lesson_datas['leader']['cheque'] . ' - liste d\'attente: ' . $lesson_datas['leader']['waiting_list'] . '"><b>' . $lesson_datas['leader']['availability'] . '</b></span></td>'
            . '<td><span class="tipsy underlined pointer" title="nb d\'inscrits: ' . $lesson_datas['follower']['count'] . ' - paiement par cheque: ' . $lesson_datas['follower']['cheque'] . ' - liste d\'attente: ' . $lesson_datas['follower']['waiting_list'] . '"><b>' . $lesson_datas['follower']['availability'] . '</b></span></td>'
            . '<td>' . $lesson->year . '</td>'
            . '<td class="center"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/' . $full_icon . '" /></td>'
            . '<td class="center"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/' . $enabled_icon . '" /></td>'
            . '<td class="center"><a href="/admin/config/sj_registration/lesson/edit/' . $lesson->sjl_id . '"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/settings.png" /></a></td>'
            . '<td class="center"><a href="/admin/config/sj_registration/lesson/delete/' . $lesson->sjl_id . '"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/stop.png" /></a></td>'
            . '</tr>';
  }
  
  $content .='</tbody></table>';
  $content .= '<a href="/admin/config/sj_registration/lesson/new">'
    . t('Créer un nouveau cours')
    . '</a><br/><br/>';
  
  $content .= '</div></fieldset>';
  
  return $content;
}

/**
 * Render student table for admin
 *
 * @param string $event
 * 
 * @return string 
 */
function render_students($event = 'cours') {
  $query = db_select('sj_students', 's');
  $query->join('sj_passes', 'p', 'p.sjp_id = s.pass_id');
  $query->rightJoin('sj_students_lessons', 'sl', 'sl.sj_student_id = s.sjs_id');
  $query->rightJoin('sj_lessons', 'l', 'l.sjl_id = sl.sj_lesson_id');
  
  $students = $query->fields('s')
          ->distinct('s.id')
          ->condition('p.year', get_filter_year())
          ->condition('l.event', $event)
          ->orderBy('payed', 'DESC')
          ->orderBy('lastname', 'ASC')
          ->execute()
          ->fetchAll();
  
  $content = '<fieldset class="collapsible collapsed">';
  $content .= '<legend><span class="fieldset-legend">' . t('Tableau des étudiants') . '</span></legend>';
  
  $content .= '<div class="fieldset-wrapper">';
  $content .= render_student_table();
  
  $content .= display_students($students, $event);
  
  $content .='</tbody></table></div></fieldset>';
  
  return $content;
}

/**
 * Sort students per lessons
 *
 * @param string $event
 * 
 * @return string 
 */
function render_students_per_lessons($event = 'cours') {
  $content = '<fieldset class="collapsible collapsed">';
  $content .= '<legend><span class="fieldset-legend">' . t('Tableau des étudiants classés par cours') . '</span></legend>';
  
  $content .= '<div class="fieldset-wrapper">';
  
  $result = db_select('sj_lessons', 'l')
          ->fields('l')
          ->condition('l.year', get_filter_year())
          ->condition('l.event', $event)
          ->execute()
          ->fetchAll();
  
  $days = array();
  foreach ($result as $lesson) {
    $days[$lesson->day][] = $lesson; 
  }
  
  foreach ($days as $lessons_per_day) {
    foreach ($lessons_per_day as $lesson) {
      $content .= '<h1>' . $lesson->name . '</h1>';
      $content .= render_student_table(false);

      $query = db_select('sj_students', 's');
      $query->join('sj_students_lessons', 'sl', 'sl.sj_student_id = s.sjs_id');

      $students = $query->fields('s')
              ->condition('sl.sj_lesson_id', $lesson->sjl_id)
              ->orderBy('payed', 'DESC')
              ->orderBy('waiting_list', 'DESC')
              ->orderBy('sl.option_list', 'DESC')
              ->orderBy('lastname', 'ASC')
              ->execute()
              ->fetchAll();

      $content .= display_students($students, $event, false, $lesson);
      $content .='</tbody></table>';
    }
  }
  
  
  
  $content .= '</div></fieldset>';
  
  return $content;
}

/**
 * Render student table
 *
 * @param boolean $details
 * @return string 
 */
function render_student_table($details = true) {
  $content = '<table><thead><tr>'
          . '<th>#</th>'
          . '<th>' . t('Prénom') . '</th>'
          . '<th>' . t('Nom') . '</th>'
          . '<th>' . t('Genre') . '</th>'
          . '<th>' . t('Email') . '</th>'
          . '<th>' . t('Téléphone') . '</th>'
          . '<th>' . t('Adresse') . '</th>'
          . '<th>' . t('Pass') . '</th>'
          . '<th>' . t('Méthode de paiement') . '</th>'
          . '<th>' . t('Payé') . '</th>'
          . '<th>' . t('Liste d\'attente') . '</th>';
  
  if (!$details) {
    $content .= '<th>' . t('Liste d\'option') . '</th>';
  }
  
  $content .= '<th>' . t('En couple') . '</th>'
          . '<th>' . t('Inscrit le') . '</th>';
  
  if ($details) {
    $content .= '<th>' . t('Inscrit aux cours') . '</th>'
            . '<th>' . t('Inscrit l\'année précédente') . '</th>';
  }
          
  $content .= '<th class="center">' . t('Actif') . '</th>'
          . '<th class="center">' . t('Editer') . '</th>'
          . '<th class="center">' . t('Supprimer') . '</th>'
          . '</tr></thead><tbody>';
  
  return $content;
}

/**
 * Display Students in table
 * 
 * @param array $students
 * @param string $event
 * @param bool  $details
 * @param stdClass $lesson
 * 
 * @return string
 */
function display_students(array $students, $event = 'cours', $details = true, $lesson = null) {
  $content = '';
  $count = 1;
  
  foreach ($students as $student) {
    if ($student->pass_id) {
      $pass = db_select('sj_passes', 'p')
              ->fields('p', array('name'))
              ->condition('sjp_id', $student->pass_id)
              ->condition('p.year', get_filter_year())
              ->execute()
              ->fetch();
    }
    
    $pass_name = isset($pass) && $pass instanceof stdClass ? $pass->name : t('Aucun pass');

    if ($student->couple_id) {
      $couple = db_select('sj_students', 's')
              ->fields('s', array('firstname', 'lastname'))
              ->condition('sjs_id', $student->couple_id)
              ->execute()
              ->fetch();
    }
    
    $couple_name = isset($couple) && $couple instanceof stdClass ? $couple->firstname . ' ' . $couple->lastname : '-';
    
    $payed_icon = $student->payed ? 'success.png' : 'stop.png';
    $waiting_list_icon = $student->waiting_list ? 'success.png' : 'stop.png';
    $registered_last_year_icon = $student->registered_last_year ? 'success.png' : 'stop.png';
    $enabled_icon = $student->enabled ? 'success.png' : 'stop.png';

    if ($lesson instanceof stdClass) {
      $registration = db_select('sj_students_lessons', 'sl')
              ->fields('sl', array('option_list'))
              ->condition('sj_student_id', $student->sjs_id)
              ->condition('sj_lesson_id', $lesson->sjl_id)
              ->execute()
              ->fetch();
      
      $option_list_icon = $registration->option_list ? 'success.png' : 'stop.png';
    }
    
    $query = db_select('sj_lessons', 'l');
    $query->join('sj_students_lessons', 'sl', 'sl.sj_lesson_id = l.sjl_id');

    if ($details) {
      $lessons = $query->fields('l', array('sjl_id', 'name'))
              ->condition('sl.sj_student_id', $student->sjs_id)
              ->condition('l.year', get_filter_year())
              ->condition('l.event', $event)
              ->execute()
              ->fetchAll();

      $lessons_list = '';
      if (count($lessons)) {
        foreach ($lessons as $registered_lesson) {
          $lessons_list .= '<span class="tipsy underlined pointer" title="' . $registered_lesson->name . '"><b>' . $registered_lesson->sjl_id . '</b></span><br/>';
        }
      }
    }

    $content .= '<tr>'
            . '<td>' . $count . '</td>'
            . '<td>' . $student->firstname . '</td>'
            . '<td>' . $student->lastname . '</td>'
            . '<td>' . $student->gender . '</td>'
            . '<td>' . $student->email . '</td>'
            . '<td>' . $student->phone . '</td>'
            . '<td>' . $student->address . ' ' . $student->postcode . ' ' . $student->city . ' ' . $student->country . '</td>'
            . '<td>' . $pass_name . '</td>'
            . '<td>' . $student->payment_method . '</td>'
            . '<td class="center"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/' . $payed_icon . '" /></td>'
            . '<td class="center"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/' . $waiting_list_icon . '" /></td>';
    
    if (isset($option_list_icon) && $option_list_icon) {
      $content .= '<td class="center"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/' . $option_list_icon . '" /></td>';
    }
    
    $content .= '<td>' . $couple_name . '</td>'
            . '<td>' . $student->created_at . '</td>';
    
    if ($details) {
      $content .= '<td>' . $lessons_list . '</td>'
              . '<td class="center"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/' . $registered_last_year_icon . '" /></td>';
    }
    
    $content .= '<td class="center"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/' . $enabled_icon . '" /></td>'
            . '<td class="center"><a href="/admin/config/sj_registration/student/edit/' . $student->sjs_id . '"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/settings.png" /></a></td>'
            . '<td class="center"><a href="/admin/config/sj_registration/student/delete/' . $student->sjs_id . '"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/stop.png" /></a></td>'
            . '</tr>';

    $count++;
  }
  
  return $content;
}

/**
 * Render places table for admin
 *
 * @return string 
 */
function render_places() {
  $places = db_select('sj_places', 'p')
              ->fields('p')
              ->condition('p.year', get_filter_year())
              ->execute()
              ->fetchAll();
  
  $content = '<fieldset class="collapsible collapsed">';
  $content .= '<legend><span class="fieldset-legend">' . t('Tableau des lieux') . '</span></legend>';
  
  $content .= '<div class="fieldset-wrapper">';
  $content .= '<table><thead><tr>'
          . '<th>#</th>'
          . '<th>' . t('Nom') . '</th>'
          . '<th>' . t('Adresse') . '</th>'
          . '<th>' . t('Code postal') . '</th>'
          . '<th>' . t('Ville') . '</th>'
          . '<th>' . t('Latitude') . '</th>'
          . '<th>' . t('Longitude') . '</th>'
          . '<th class="center">' . t('Actif') . '</th>'
          . '<th class="center">' . t('Editer') . '</th>'
          . '<th class="center">' . t('Supprimer') . '</th>'
          . '</tr></thead><tbody>';
  
  foreach($places as $place) {
    $enabled_icon = $place->enabled ? 'success.png' : 'stop.png';
    
    $content .= '<tr>'
            . '<td>' . $place->id . '</td>'
            . '<td>' . $place->name . '</td>'
            . '<td>' . $place->address . '</td>'
            . '<td>' . $place->postcode . '</td>'
            . '<td>' . $place->city . '</td>'
            . '<td>' . $place->latitude . '</td>'
            . '<td>' . $place->longitude . '</td>'
            . '<td class="center"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/' . $enabled_icon . '" /></td>'
            . '<td class="center"><a href="/admin/config/sj_registration/place/edit/' . $place->id . '"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/settings.png" /></a></td>'
            . '<td class="center"><a href="/admin/config/sj_registration/place/delete/' . $place->id . '"><img width="20px" src="http://' . $_SERVER['HTTP_HOST'] . '/sites/all/themes/sjamelia/assets/images/icon/stop.png" /></a></td>'
            . '</tr>';
  }
  
  $content .='</tbody></table>';
  $content .= '<a href="/admin/config/sj_registration/place/new">'
    . t('Créer un nouveau lieu')
    . '</a><br/><br/>';
  
  $content .= '</div></fieldset>';
  
  return $content;
}