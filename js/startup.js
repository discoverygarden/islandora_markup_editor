var dsid = "OBJ";
//window.onload = function() {
	
	//cwrcWriterInit(Writer, Delegator);
	function cwrcWriterInit(Writer, Delegator) {
		cwrc_params = {};
		
		writer = null;
		
		function doResize() {
			var uiHeight = $('#'+writer.editor.id+'_tbl tr.mceFirst').outerHeight() + 2;
			writer.editor.theme.resizeTo($(window).width(), $(window).height() - uiHeight);
		}
		
		var baseUrl = window.location.protocol+'//'+window.location.host;
		console.log(baseUrl);
		var config = {
			id: 'editor',
			delegator: Delegator,
			cwrcRootUrl: baseUrl+'/editor/test/',
			buttons1: 'schematags,removeTag,|,addperson,addplace,|,viewsource',
			schemas: {
				tei: {
					name: 'CWRC Basic TEI Schema',
					url: baseUrl+'/schema/CWRC-TEIBasic.rng',
					cssUrl: baseUrl+'/editor/test/css/tei_converted.css'
				},
				events: {
					name: 'Events Schema',
					url: baseUrl+'/schema/events.rng',
					cssUrl: baseUrl+'/editor/test/css/orlando_converted.css'
				},
				biography: {
					name: 'Biography Schema',
					url: baseUrl+'/schema/biography.rng',
					cssUrl: baseUrl+'/editor/test/css/orlando_converted.css'
				},
				writing: {
					name: 'Writing Schema',
					url: baseUrl+'/schema/writing.rng',
					cssUrl: baseUrl+'/editor/test/css/orlando_converted.css'
				}
			}
		};
		
		$.ajax({
			url: 'http://apps.testing.cwrc.ca/editor/documents/info/projectname',
			timeout: 3000,
			success: function(data, status, xhr) {
				config.project = data;
				writer = new Writer(config);
				writer.event('writerInitialized').subscribe(doResize);
				$(window).on('resize', doResize);
			},
			error: function() {
				config.cwrcRootUrl = baseUrl+'/cwrc/src/';
				config.schemas = {
					tei: {
						name: 'CWRC Basic TEI Schema',
						url: baseUrl+'/cwrc/src/schema/CWRC-TEIBasic.rng',
						cssUrl: baseUrl+'/cwrc/src/css/tei_converted.css'
					},
					events: {
						name: 'Events Schema',
						url: baseUrl+'/cwrc/src/schema/events.rng',
						cssUrl: baseUrl+'/cwrc/src/css/orlando_converted.css'
					},
					biography: {
						name: 'Biography Schema',
						url: baseUrl+'/cwrc/src/schema/biography.rng',
						cssUrl: baseUrl+'/cwrc/src/css/orlando_converted.css'
					},
					writing: {
						name: 'Writing Schema',
						url: baseUrl+'/cwrc/src/schema/writing.rng',
						cssUrl: baseUrl+'/cwrc/src/css/orlando_converted.css'
					}
				};
				writer = new Writer(config);
				writer.event('writerInitialized').subscribe(doResize);
				$(window).on('resize', doResize);
			}
		});
	};
	
	
	
	
  // Hide the content we dont need.
//  $('#page_selector').hide();
//  $('#header-inner').hide();
//  $('#pageChange').hide();
//  $('#header_label_wrapper').hide();
//  $('#annotation_tab').hide();

//  PID = Drupal.settings.islandora_markup_editor.page_pid;
//  cwrc_params = {};
//  window.location.hash = '#' + PID;
//  writer = null;
//  moduleUrl = Drupal.settings.basePath +
//    Drupal.settings.islandora_markup_editor.module_edit_base;
//  var config = {
//    delegator: islandoraBackendDelegate,
//    cwrcRootUrl: moduleUrl + '/CWRC-Writer/src/',
//    schemas: Drupal.settings.islandora_markup_editor.schema_object['schemas']
//  };
//  $.ajax({
//    url: Drupal.settings.basePath + Drupal.settings.islandora_markup_editor.page_setup + PID,
//    timeout: 3000,
//    async: false,
//    dataType: 'json',
//    success: function(data, status, xhr) {
//      cwrc_params = data;
//      config.project = data;
//      writer = new Writer(config);
//      writer.currentDocId = PID;
//      writer.schemaId = "doc_default";
//      writer.init();
//      // Close the UIPanes.
//     // writer.layout.hide("east");
//      //writer.layout.toggle("west");
//    },
//    error: function() {
//      console.log("Error");
//    }
//  });
//}