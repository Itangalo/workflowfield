<?php
// $Id$

/**
 * @file
 * Provides basic functions for using list fields for workflows.
 */

/**
 * Implementation of hook_rules_event_info().
 *
 * This function declares all the possible workflow transition events.
 */
function workflowfield_rules_event_info() {
  // Get all the workflow fields, for all node types.
  $workflow_fields = workflowfield_get_fields();

  // Build up all the possible events for the workflow fields.
  $events = array();
  foreach ($workflow_fields as $workflow_field) {
    $transitions = workflowfield_get_all_transitions($workflow_field);

    foreach ($transitions as $key => $transition) {
      $events['workflow_' . $workflow_field['field_name'] . '_' . $key] = array(
        'label' => $transition,
        'module' => t('Workflow: @field', array('@field' => $workflow_field['field_name'])),
        'arguments' => array(
          'node' => array('type' => 'node', 'label' => t('updated content')),
          'unsaved_node' => array('type' => 'user', 'label' => t('unsaved content')),
          'account' => array('type' => 'user', 'label' => t('acting user')),
          'author' => array('type' => 'user', 'label' => t('node author')),
        ),
      );
    }
  }

  return $events;
}
