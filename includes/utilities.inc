<?php
/**
 * @file
 * Handles the creation/display of islandora:markupEditorCModel objects.
 */

/**
 * Return an objects datastreams xml processing instructions.
 *
 * @param AbstractObject $object
 *   The Fedora object to act on.
 * @param string $dsid
 *   The datastream ID to use as source content. Defaults to OBJ.
 *
 * @return boolean|array
 *   An indexed array of processing instuctions, or FALSE if not found.
 */
function islandora_markup_editor_fetch_tei_processing_instruction(AbstractObject $object, $dsid = 'OBJ') {

  if (!isset($object[$dsid])) {
    return FALSE;
  }

  $result = islandora_markup_editor_query_for_processing_instruction($object[$dsid]->content);

  if (!$result->item(0)) {
    // No processing instruction, add the default.
    islandora_markup_editor_add_tei_processing_instruction($object, "", $dsid);
    $result = islandora_markup_editor_query_for_processing_instruction($object[$dsid]->content);
  }

  // Format the output for convience.
  $arr = explode(" ", $result->item(0)->data);
  $return = array();
  foreach ($arr as $key => $value) {
    $split_arr = explode("=", $value);
    $return[$split_arr[0]] = str_replace('"', '', $split_arr[1]);
  }
  return $return;
}

/**
 * Query a FedoraObjects datastream for an xml processor instruction.
 *
 * @param string $xml
 *   The xml string to query for processing instruction.
 *
 * @return string
 *   The processing instruction as a string.
 */
function islandora_markup_editor_query_for_processing_instruction($xml) {
  $xml_data = $xml;
  $src_doc = new DOMDocument();
  $src_doc->preserveWhiteSpace = FALSE;
  $src_doc->formatOutput = TRUE;
  @$src_doc->loadXML($xml_data);

  $xpath = new DOMXPath($src_doc);
  $e = $xpath->query('//processing-instruction(\'xml-model\')');
  return $e;
}

/**
 * Load js/css files in a given directory for the cwrc editor.
 *
 * @param string $direc
 *   The directory the files reside in.
 * @param string $file_type
 *   For now, ither .js or .css.
 */
function islandora_markup_editor_add_files_from_dir($direc, $file_type = 'js') {
  $function = "drupal_add_" . $file_type;
  if (!function_exists($function)) {
    return FALSE;
  }
  $dir = new DirectoryIterator($direc);
  foreach ($dir as $fileinfo) {
    if (!$fileinfo->isDot() && $fileinfo->isFile() && ($fileinfo->getExtension() == $file_type)) {
      $file_name = $fileinfo->getFilename();
      $function($direc . "/$file_name");
    }
  }
}

/**
 * Adds schema processing instructions to a given objects requested datastream.
 *
 * @param AbstractObject $object
 *   The fedora object to act upon.
 * @param string $schema
 *   The accessable url to a relaxng .rng schema
 * @param string $dsid
 *   The dsid to add instructions to. Defaults to OBJ.
 *
 * @return string
 *   The processing instruction as it appears in the given datastream.
 */
function islandora_markup_editor_add_tei_processing_instruction(AbstractObject $object, $schema, $dsid = 'OBJ') {
  if ($schema == "") {
    $markup_editor_module_path = drupal_get_path('module', 'islandora_markup_editor');
    // Use the CWRC-TEIBasic.rng provided with the cwrc-writer by default.
    $schema = file_create_url("$markup_editor_module_path/CWRC-Writer/src/schema/CWRC-TEIBasic.rng");
  }
  $xml_data = $object[$dsid]->content;
  $instructions = array(
    'href' => $schema,
    'type' => 'application/xml',
    'schematypens' => 'http://relaxng.org/ns/structure/1.0',
  );

  $tei_doc = new DOMDocument();
  @$tei_doc->loadXML($xml_data);

  $processing_string = "";
  foreach ($instructions as $key => $value) {
    $processing_string .= $key . '="' . $value . '" ';
  }
  $trimmed = trim($processing_string);

  $src_doc = new DOMDocument("1.0", "ISO-8859-15");
  $src_doc->preserveWhiteSpace = FALSE;
  $src_doc->formatOutput = TRUE;
  $rng_schema = $src_doc->createProcessingInstruction('xml-model', $trimmed);
  $src_doc->appendChild($rng_schema);
  $node = $tei_doc->getElementsByTagName('TEI')->item(0);
  $tei_data = $src_doc->importNode($node, TRUE);
  $src_doc->appendChild($tei_data);
  $data = $src_doc->saveXML();
  $object['OBJ']->setContentFromString($data);

  return $trimmed;
}
