<?php
/**
 * @file
 * Handles the theme requirements for islandora_markup_editor module.
 */

/**
 * Implements hook_preprocess().
 */
function islandora_markup_editor_preprocess_islandora_markup_editor(&$variables) {
  module_load_include('inc', 'islandora_markup_editor', 'includes/utilities');
  $module_path = drupal_get_path('module', 'islandora_markup_editor');

  // Add custom drupal settings for this implementation of the
  // CWRC-Writer library.
  islandora_markup_editor_add_markup_editor_drupal_settings($variables);

  // Add the CWRC-Writer library.
  drupal_add_library('islandora_markup_editor', 'cwrcwriter');

  // Add our custom css files.
  islandora_markup_editor_add_files_from_dir($module_path . "/css", "css");

  // Uses the $variables['custom_js'] to flag this theme preprocess from
  // another module, indicating an override to the default initilization of
  // the markup editor module.
  $custom_js = isset($variables['custom_js']) ? $variables['custom_js'] : $module_path . "/js";

  // Mindlessly add js files from the supplied directory.
  if ($custom_js !== TRUE) {
    islandora_markup_editor_add_files_from_dir($custom_js);
  }
}
