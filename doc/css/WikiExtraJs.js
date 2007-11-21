/* generated javascript */
var skin = 'monobook';
var stylepath = '/pixiewiki_install/skins';

/* MediaWiki:Common.js */
/* Any JavaScript here will be loaded for all users on every page load. */

 var isViewingMainPage = (/^Main Page(\/..)? - PixieWiki$/.test(document.title));
 if (isViewingMainPage) {
  if (wgUserName != "Geohar") {
 	document.write('<style type="text/css">/*<![CDATA[*/ #lastmod, #siteSub, h1.firstHeading { display: none !important; }  #content { padding-top: 1em; } #jump-to-nav { display: none !important; }  #p-cactions, #p-tb { display:none; } /*]]>*/</style>');
  } else {
 	document.write('<style type="text/css">/*<![CDATA[*/ #lastmod, #siteSub, h1.firstHeading { display: none !important; }  #content { padding-top: 1em; } /*]]>*/</style>');
  }
 }
 
 if (mwCustomEditButtons) {
   mwCustomEditButtons[mwCustomEditButtons.length] = {
     "imageFile": "http://george-graphics.co.uk/pixiewiki_install/skins/common/images/button_tt.png",
     "speedTip": "tellytype",
     "tagOpen": "<tt>",
     "tagClose": "</tt>",
     "sampleText": "Insert text"};
 }

/* MediaWiki:Monobook.js (deprecated; migrate to Common.js!) */
/* Deprecated; use [[MediaWiki:common.js]] */