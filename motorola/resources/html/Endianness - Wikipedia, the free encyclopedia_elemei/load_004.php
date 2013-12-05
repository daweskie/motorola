mw.loader.implement("ext.articleFeedbackv5.startup",function(){jQuery(function($){var removeOld,load,statusChangeSuccess,statusCallback,enable=$.aftUtils.verify('article');removeOld=function(){var remove,interval,initTime=new Date();remove=function(){var $aft=$('#mw-articlefeedback'),timeDiff=((new Date()).getTime()-initTime.getTime())/1000;if($aft.length>0){$aft.remove();clearInterval(interval);}else if(timeDiff>5){clearInterval(interval);}};interval=setInterval(remove,100);};load=function(){removeOld();mw.loader.load('ext.articleFeedbackv5');if(navigator.appVersion.indexOf('MSIE 7')!==-1){mw.loader.load('ext.articleFeedbackv5.ie');}};statusChangeSuccess=function(){var display,interval;display=function(){var $form=$('#mw-articlefeedbackv5'),link;if($form.length===0){return;}$.articleFeedbackv5.highlightForm();link=mw.config.get('wgArticleFeedbackv5SpecialUrl')+'/'+mw.config.get('wgPageName');$('<p id="articleFeedbackv5-added"></p>').msg('articlefeedbackv5-enabled-form-message',link).
appendTo($form);clearTimeout(interval);};interval=setInterval(display,100);};statusCallback=function(data,error){if(data!==false){$link.remove();if(!enable){load();}statusChangeSuccess();}else if(error){alert(error);}};if(enable){load();}var article=$.aftUtils.article();if(mw.config.get('wgArticleFeedbackv5EnableProtection',1)&&!$.aftUtils.whitelist(article)&&!$.aftUtils.blacklist(article)&&$.aftUtils.canSetStatus(true)){var userPermissions=mw.config.get('wgArticleFeedbackv5Permissions');var $link=$('<li id="t-articlefeedbackv5-enable"><a href="#"></a></li>');$link.find('a').text(mw.msg('articlefeedbackv5-toolbox-enable'));if('aft-administrator'in userPermissions&&userPermissions['aft-administrator']){var link=mw.config.get('wgScript')+'?title='+encodeURIComponent(mw.config.get('wgPageName'))+'&'+$.param({action:'protect'});$link.find('a').attr('href',link);}else{$link.find('a').on('click',function(e){e.preventDefault();$.aftUtils.setStatus(article.id,1,statusCallback);});}$('#p-tb').
find('ul').append($link);}});;},{},{"articlefeedbackv5-toolbox-enable":"Enable feedback","articlefeedbackv5-enabled-form-message":"Feedback has just been enabled. Reader posts will be visible [$1 at the feedback page]."});mw.loader.implement("ext.cite",function(){(function(mw,$){'use strict';mw.hook('wikipage.content').add(function($content){var accessibilityLabelOne=mw.msg('cite_references_link_accessibility_label'),accessibilityLabelMany=mw.msg('cite_references_link_many_accessibility_label');$content.find('.mw-cite-backlink').each(function(){var $links=$(this).find('a'),label;if($links.length>1){label=accessibilityLabelMany;}else{label=accessibilityLabelOne;}$links.eq(0).prepend($('<span>').addClass('cite-accessibility-label').text(label+' '));});});})(mediaWiki,jQuery);;},{"css":[
".cite-accessibility-label{position:absolute !important; top:-99999px;clip:rect(1px 1px 1px 1px); clip:rect(1px,1px,1px,1px);padding:0 !important;border:0 !important;height:1px !important;width:1px !important;overflow:hidden}\n/* cache key: enwiki:resourceloader:filter:minify-css:7:6989008023386f50501783f5c5ff5345 */"]},{"cite_references_link_accessibility_label":"Jump up","cite_references_link_many_accessibility_label":"Jump up to:"});mw.loader.implement("jquery.articleFeedbackv5.utils",function(){(function($){$.aftUtils={};$.aftUtils.article=function(){var article=jQuery.extend({},mw.config.get('aftv5Article'));if($.inArray(mw.config.get('wgNamespaceNumber'),mw.config.get('wgArticleFeedbackv5Namespaces',[]))>-1){article.id=mw.config.get('wgArticleId',-1);article.namespace=mw.config.get('wgNamespaceNumber');article.categories=mw.config.get('wgCategories',[]);}return article;};$.aftUtils.verify=function(location){$.aftUtils.removeLegacyCookies();var article=$.aftUtils.article();var
enable=true;enable&=$.aftUtils.useragent();enable&=mw.config.get('wgArticleFeedbackv5Namespaces',[]).length>0;if(location!='special'||article.id!=0){enable&=$.inArray(article.namespace,mw.config.get('wgArticleFeedbackv5Namespaces',[]))>-1;enable&=mw.config.get('wgAction')!='edit';enable&=!mw.config.get('wgPostEdit',false);}if(location!='special'){if(mw.config.get('wgArticleFeedbackv5EnableProtection',1)&&article.permissionLevel!==false){enable&=$.aftUtils.permissions(article,article.permissionLevel);}else{var defaultPermissionLevel=$.aftUtils.getDefaultPermissionLevel(article);enable&=$.aftUtils.permissions(article,defaultPermissionLevel)||$.aftUtils.whitelist(article);}enable&=!$.aftUtils.blacklist(article);}if(location=='article'){enable&=!mw.user.options.get('articlefeedback-disable');enable&=(mw.config.get('wgAction')=='view'||mw.config.get('wgAction')=='purge');enable&=!(mw.config.get('wgAction')=='purge'&&mw.user.anonymous());enable&=mw.util.getParamValue('diff')==null;enable&=mw
.util.getParamValue('oldid')==null;enable&=mw.util.getParamValue('redirect')!='no';enable&=mw.util.getParamValue('printable')!='yes';}return enable;};$.aftUtils.permissions=function(article,permissionLevel){var permissions=mw.config.get('wgArticleFeedbackv5Permissions');return permissionLevel in permissions&&permissions[permissionLevel];};$.aftUtils.blacklist=function(article){var blacklistCategories=mw.config.get('wgArticleFeedbackv5BlacklistCategories',[]);var intersect=$.map(blacklistCategories,function(category){return $.inArray(category.replace(/_/g,' '),article.categories)<0?null:category;});return intersect.length>0;};$.aftUtils.whitelist=function(article){var whitelistCategories=mw.config.get('wgArticleFeedbackv5Categories',[]);var intersect=$.map(whitelistCategories,function(category){return $.inArray(category.replace(/_/g,' '),article.categories)<0?null:category;});return intersect.length>0;};$.aftUtils.lottery=function(article){var odds=mw.config.get(
'wgArticleFeedbackv5LotteryOdds',0);if(typeof odds==='object'&&article.namespace in odds){odds=odds[article.namespace];}return(Number(article.id)%1000)>=(1000-(Number(odds)*10));};$.aftUtils.getDefaultPermissionLevel=function(article){return $.aftUtils.lottery(article)?'aft-reader':'aft-noone';};$.aftUtils.useragent=function(){var ua=navigator.userAgent.toLowerCase();return!(ua.indexOf('msie 6')!=-1||ua.indexOf('firefox/2.')!=-1||ua.indexOf('firefox 2.')!=-1||ua.indexOf('android')!=-1);};$.aftUtils.getCookieName=function(suffix){return'AFTv5-'+suffix;};$.aftUtils.removeLegacyCookies=function(){var legacyCookieName=function(suffix){return'ext.articleFeedbackv5@11-'+suffix;};$.cookie(legacyCookieName('activity'),null,{expires:-1,path:'/'});$.cookie(legacyCookieName('last-filter'),null,{expires:-1,path:'/'});$.cookie(legacyCookieName('submission_timestamps'),null,{expires:-1,path:'/'});$.cookie(legacyCookieName('feedback-ids'),null,{expires:-1,path:'/'});};$.aftUtils.canSetStatus=function
(enable){var permissionLevel=$.aftUtils.article().permissionLevel||$.aftUtils.getDefaultPermissionLevel($.aftUtils.article());var userPermissions=mw.config.get('wgArticleFeedbackv5Permissions');var enabled=(permissionLevel==='aft-reader');if(!('aft-editor'in userPermissions)||!userPermissions['aft-editor']){return false;}if($.aftUtils.article().permissionLevel===false&&!enabled){permissionLevel='aft-editor';}if(!(permissionLevel in userPermissions)||!userPermissions[permissionLevel]){return false;}return enable!=enabled;};$.aftUtils.setStatus=function(pageId,enable,callback){var api=new mw.Api();api.post({'pageid':pageId,'enable':parseInt(enable),'format':'json','action':'articlefeedbackv5-set-status'}).done(function(data){if(typeof callback==='function'){if('articlefeedbackv5-set-status'in data){callback(data['articlefeedbackv5-set-status'],null);}}}).fail(function(code,data){var message=mw.msg('articlefeedbackv5-error-unknown');if('error'in data&&'info'in data.error){message=data.
error.info;}if(typeof callback==='function'){callback(false,message);}else{alert(message);}});};})(jQuery);;},{},{"articlefeedbackv5-error-unknown":"Unknown error."});mw.loader.implement("jquery.makeCollapsible",function(){(function($,mw){var lpx='jquery.makeCollapsible> ';function toggleElement($collapsible,action,$defaultToggle,options){var $collapsibleContent,$containers,hookCallback;options=options||{};if(!$collapsible.jquery){return;}if(action!=='expand'&&action!=='collapse'){return;}if($defaultToggle===undefined){$defaultToggle=null;}if($defaultToggle!==null&&!$defaultToggle.jquery){return;}$collapsible.trigger(action==='expand'?'beforeExpand.mw-collapsible':'beforeCollapse.mw-collapsible');hookCallback=function(){$collapsible.trigger(action==='expand'?'afterExpand.mw-collapsible':'afterCollapse.mw-collapsible');};if(!options.plainMode&&$collapsible.is('table')){$containers=$collapsible.find('> tbody > tr');if($defaultToggle){$containers=$containers.not($defaultToggle.closest(
'tr'));}if(action==='collapse'){if(options.instantHide){$containers.hide();hookCallback();}else{$containers.stop(true,true).fadeOut().promise().done(hookCallback);}}else{$containers.stop(true,true).fadeIn().promise().done(hookCallback);}}else if(!options.plainMode&&($collapsible.is('ul')||$collapsible.is('ol'))){$containers=$collapsible.find('> li');if($defaultToggle){$containers=$containers.not($defaultToggle.parent());}if(action==='collapse'){if(options.instantHide){$containers.hide();hookCallback();}else{$containers.stop(true,true).slideUp().promise().done(hookCallback);}}else{$containers.stop(true,true).slideDown().promise().done(hookCallback);}}else{$collapsibleContent=$collapsible.find('> .mw-collapsible-content');if(!options.plainMode&&$collapsibleContent.length){if(action==='collapse'){if(options.instantHide){$collapsibleContent.hide();hookCallback();}else{$collapsibleContent.slideUp().promise().done(hookCallback);}}else{$collapsibleContent.slideDown().promise().done(
hookCallback);}}else{if(action==='collapse'){if(options.instantHide){$collapsible.hide();hookCallback();}else{if($collapsible.is('tr')||$collapsible.is('td')||$collapsible.is('th')){$collapsible.fadeOut().promise().done(hookCallback);}else{$collapsible.slideUp().promise().done(hookCallback);}}}else{if($collapsible.is('tr')||$collapsible.is('td')||$collapsible.is('th')){$collapsible.fadeIn().promise().done(hookCallback);}else{$collapsible.slideDown().promise().done(hookCallback);}}}}}function togglingHandler($toggle,$collapsible,e,options){var wasCollapsed,$textContainer,collapseText,expandText;if(options===undefined){options={};}if(e){if(e.type==='click'&&options.linksPassthru&&$.nodeName(e.target,'a')){return;}else if(e.type==='keypress'&&e.which!==13&&e.which!==32){return;}else{e.preventDefault();e.stopPropagation();}}if(options.wasCollapsed!==undefined){wasCollapsed=options.wasCollapsed;}else{wasCollapsed=$collapsible.hasClass('mw-collapsed');}$collapsible.toggleClass('mw-collapsed'
,!wasCollapsed);if(options.toggleClasses){$toggle.toggleClass('mw-collapsible-toggle-collapsed',!wasCollapsed).toggleClass('mw-collapsible-toggle-expanded',wasCollapsed);}if(options.toggleText){collapseText=options.toggleText.collapseText;expandText=options.toggleText.expandText;$textContainer=$toggle.find('> a');if(!$textContainer.length){$textContainer=$toggle;}$textContainer.text(wasCollapsed?collapseText:expandText);}toggleElement($collapsible,wasCollapsed?'expand':'collapse',$toggle,options);}$.fn.makeCollapsible=function(options){if(options===undefined){options={};}return this.each(function(){var $collapsible,collapseText,expandText,$toggle,actionHandler,buildDefaultToggleLink,premadeToggleHandler,$toggleLink,$firstItem,collapsibleId,$customTogglers,firstval;$collapsible=$(this).addClass('mw-collapsible');if($collapsible.data('mw-made-collapsible')){return;}else{$collapsible.data('mw-made-collapsible',true);}collapseText=options.collapseText||$collapsible.attr('data-collapsetext'
)||mw.msg('collapsible-collapse');expandText=options.expandText||$collapsible.attr('data-expandtext')||mw.msg('collapsible-expand');actionHandler=function(e,opts){var defaultOpts={toggleClasses:true,toggleText:{collapseText:collapseText,expandText:expandText}};opts=$.extend(defaultOpts,options,opts);togglingHandler($(this),$collapsible,e,opts);};buildDefaultToggleLink=function(){return $('<a href="#"></a>').text(collapseText).wrap('<span class="mw-collapsible-toggle"></span>').parent().prepend('&nbsp;[').append(']&nbsp;').on('click.mw-collapsible keypress.mw-collapsible',actionHandler);};premadeToggleHandler=function(e,opts){var defaultOpts={toggleClasses:true,linksPassthru:true};opts=$.extend(defaultOpts,options,opts);togglingHandler($(this),$collapsible,e,opts);};if(options.$customTogglers){$customTogglers=$(options.$customTogglers);}else{collapsibleId=$collapsible.attr('id')||'';if(collapsibleId.indexOf('mw-customcollapsible-')===0){mw.log(lpx+'Found custom collapsible: #'+
collapsibleId);$customTogglers=$('.'+collapsibleId.replace('mw-customcollapsible','mw-customtoggle'));if(!$customTogglers.length){mw.log(lpx+'#'+collapsibleId+': Missing toggler!');}}}if($customTogglers&&$customTogglers.length){actionHandler=function(e,opts){var defaultOpts={};opts=$.extend(defaultOpts,options,opts);togglingHandler($(this),$collapsible,e,opts);};$toggleLink=$customTogglers;$toggleLink.on('click.mw-collapsible keypress.mw-collapsible',actionHandler);}else{if($collapsible.is('table')){$firstItem=$collapsible.find('tr:first th, tr:first td');$toggle=$firstItem.find('> .mw-collapsible-toggle');if(!$toggle.length){$toggleLink=buildDefaultToggleLink().prependTo($firstItem.eq(-1));}else{actionHandler=premadeToggleHandler;$toggleLink=$toggle.on('click.mw-collapsible keypress.mw-collapsible',actionHandler);}}else if($collapsible.is('ul')||$collapsible.is('ol')){$firstItem=$collapsible.find('li:first');$toggle=$firstItem.find('> .mw-collapsible-toggle');if(!$toggle.length){
firstval=$firstItem.attr('value');if(firstval===undefined||!firstval||firstval==='-1'||firstval===-1){$firstItem.attr('value','1');}$toggleLink=buildDefaultToggleLink();$toggleLink.wrap('<li class="mw-collapsible-toggle-li"></li>').parent().prependTo($collapsible);}else{actionHandler=premadeToggleHandler;$toggleLink=$toggle.on('click.mw-collapsible keypress.mw-collapsible',actionHandler);}}else{$toggle=$collapsible.find('> .mw-collapsible-toggle');if(!$collapsible.find('> .mw-collapsible-content').length){$collapsible.wrapInner('<div class="mw-collapsible-content"></div>');}if(!$toggle.length){$toggleLink=buildDefaultToggleLink().prependTo($collapsible);}else{actionHandler=premadeToggleHandler;$toggleLink=$toggle.on('click.mw-collapsible keypress.mw-collapsible',actionHandler);}}}$toggleLink.prop('tabIndex',0);if(options.collapsed||$collapsible.hasClass('mw-collapsed')){actionHandler.call($toggleLink.get(0),null,{instantHide:true,wasCollapsed:false});}});};}(jQuery,mediaWiki));;},{
"css":[".mw-collapsible-toggle{float:right} li .mw-collapsible-toggle{float:none} .mw-collapsible-toggle-li{list-style:none}\n/* cache key: enwiki:resourceloader:filter:minify-css:7:4250852ed2349a0d4d0fc6509a3e7d4c */"]},{"collapsible-expand":"expand","collapsible-collapse":"collapse"});mw.loader.implement("mediawiki.action.view.postEdit",function(){(function(mw,$){'use strict';var config=mw.config.get(['wgAction','wgCookiePrefix','wgCurRevisionId']),cookieKey=config.wgCookiePrefix+'PostEditRevision'+config.wgCurRevisionId,$div,id;function showConfirmation(data){data=data||{};if(data.message===undefined){data.message=$.parseHTML(mw.message('postedit-confirmation',data.user||mw.user).escaped());}$div=$('<div class="postedit-container">'+'<div class="postedit">'+'<div class="postedit-icon postedit-icon-checkmark postedit-content"></div>'+'<a href="#" class="postedit-close">&times;</a>'+'</div>'+'</div>');if(typeof data.message==='string'){$div.find('.postedit-content').text(data.message)
;}else if(typeof data.message==='object'){$div.find('.postedit-content').append(data.message);}$div.click(fadeOutConfirmation).prependTo('body');id=setTimeout(fadeOutConfirmation,3000);}function fadeOutConfirmation(){clearTimeout(id);$div.find('.postedit').addClass('postedit postedit-faded');setTimeout(removeConfirmation,500);return false;}function removeConfirmation(){$div.remove();mw.hook('postEdit.afterRemoval').fire();}mw.hook('postEdit').add(showConfirmation);if(config.wgAction==='view'&&$.cookie(cookieKey)==='1'){$.cookie(cookieKey,null,{path:'/'});mw.config.set('wgPostEdit',true);mw.hook('postEdit').fire();}}(mediaWiki,jQuery));;},{"css":[
".postedit-container{margin:0 auto;position:fixed;top:0;height:0;left:50%;z-index:1000;font-size:13px}.postedit-container:hover{cursor:pointer}.postedit{position:relative;top:0.6em;left:-50%;padding:.6em 3.6em .6em 1.1em;line-height:1.5625em;color:#626465;background-color:#f4f4f4;border:1px solid #dcd9d9;text-shadow:0 0.0625em 0 rgba(255,255,255,0.5);border-radius:5px;-webkit-box-shadow:0 2px 5px 0 #ccc;box-shadow:0 2px 5px 0 #ccc;-webkit-transition:all 0.25s ease-in-out;-moz-transition:all 0.25s ease-in-out;-ms-transition:all 0.25s ease-in-out;-o-transition:all 0.25s ease-in-out;transition:all 0.25s ease-in-out}.skin-monobook .postedit{top:6em !important}.postedit-faded{opacity:0}.postedit-icon{padding-left:41px;  line-height:25px;background-repeat:no-repeat;background-position:8px 50%}.postedit-icon-checkmark{background-image:url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAMAAAAoLQ9TAAABblBMVEUAAAD///////9PfTf///80aRdTgjn///9Feij///////////9Rfzf///////////9PfjZRgDh1o1xOfTb///////+bwYqLtnj///////9PfTa82K////9WhT6YxIL///9QgDdTgzr////////j7uDl7eLq8efi693k7OH///////9UhjuBr2rp9uRUhjr///9YljVKgir///9WiTlYjT3////9/v57vFlbkT5PjC9dlD/5/fhuq09stUTs9uhxuElctCpfnT1huDFloEZloUZmpENmvDZpvDxpvTxqvjxrvT5rvT9rwTxsqktswD5uwkBvuUdxw0NztFBztU9ztVBzwkp0tlJ1xkd2t1R3uVR4w1F4xk54x014yE15uVZ5v1R5xVB6v1R7yFJ8wVh9xVl9yFR9yVd9ylN+xVh+yFd/x1l/yFeAylmEx1+Ny2uY0Hqe04Wj1Ymv3Ze33qLD47TJ5L3O6cPU7Mrq9eb2+/Q4j37OAAAAQHRSTlMAAQIEBAUFBQwPFB4fJCUoKiosQEhJS01RUlZZXmdydXaChYuSlJSWmJmoq6uur8LExcvM19fg5ejt8fX2+Pr7SljgewAAAKpJREFUGBkFwQNCAwAAAMDLtl3LtrG4rWXbtvX77gAgZ6grFwC0bhwNVgKgdPZx8b0dgLi+s7Wn0VoAqpfOI9+BNADZI7fLrz2pSEwGHZuH+78lSK8ZLkLezF3ooyUG3VPXq2USei9WngeyoG195yBYWDF3E/2pAhl1e9Gr8bGT+bfOFCC2fnvh4X7rcqIAQNNu+HT6sxkAjceTL/2ZAIhv+PorBwBJxfkA//dFHSCBy/UTAAAAAElFTkSuQmCC);background-image:url(//bits.wikimedia.org/static-1.23wmf4/resources/mediawiki.action/images/green-checkmark.png?2013-11-14T18:10:00Z)!ie;background-position:left}.postedit-close{position:absolute;padding:0 .8em;right:0;top:0;font-size:1.25em;font-weight:bold;line-height:2.3em;color:black;text-shadow:0 0.0625em 0 white;text-decoration:none;opacity:0.2;filter:alpha(opacity=20)}.postedit-close:hover{color:black;text-decoration:none;opacity:0.4;filter:alpha(opacity=40)}\n/* cache key: enwiki:resourceloader:filter:minify-css:7:6282247611d5f95fa0dbf2f6ce149283 */"
]},{"postedit-confirmation":"Your edit was saved."});mw.loader.implement("mediawiki.searchSuggest",function(){(function(mw,$){$(function(){var map,resultRenderCache,searchboxesSelectors,$searchRegion=$('#simpleSearch, #searchInput').first(),$searchInput=$('#searchInput');map={browsers:{ltr:{opera:[['>=',9.6]],docomo:false,blackberry:false,ipod:false,iphone:false},rtl:{opera:[['>=',9.6]],docomo:false,blackberry:false,ipod:false,iphone:false}}};if(!$.client.test(map)){return;}function computeResultRenderCache(context){var $form,formAction,baseHref,linkParams;$form=context.config.$region.closest('form');formAction=$form.attr('action');baseHref=formAction+(formAction.match(/\?/)?'&':'?');linkParams={};$.each($form.serializeArray(),function(idx,obj){linkParams[obj.name]=obj.value;});return{textParam:context.data.$textbox.attr('name'),linkParams:linkParams,baseHref:baseHref};}function renderFunction(text,context){if(!resultRenderCache){resultRenderCache=computeResultRenderCache(context);}
resultRenderCache.linkParams[resultRenderCache.textParam]=text;this.append($('<span>').css('whiteSpace','nowrap').text(text)).wrap($('<a>').attr('href',resultRenderCache.baseHref+$.param(resultRenderCache.linkParams)).addClass('mw-searchSuggest-link'));}function specialRenderFunction(query,context){var $el=this;if(!resultRenderCache){resultRenderCache=computeResultRenderCache(context);}resultRenderCache.linkParams[resultRenderCache.textParam]=query;if($el.children().length===0){$el.append($('<div>').addClass('special-label').text(mw.msg('searchsuggest-containing')),$('<div>').addClass('special-query').text(query).autoEllipsis()).show();}else{$el.find('.special-query').text(query).autoEllipsis();}if($el.parent().hasClass('mw-searchSuggest-link')){$el.parent().attr('href',resultRenderCache.baseHref+$.param(resultRenderCache.linkParams)+'&fulltext=1');}else{$el.wrap($('<a>').attr('href',resultRenderCache.baseHref+$.param(resultRenderCache.linkParams)+'&fulltext=1').addClass(
'mw-searchSuggest-link'));}}searchboxesSelectors=['#searchInput','#powerSearchText','#searchText','.mw-searchInput'];$(searchboxesSelectors.join(', ')).suggestions({fetch:function(query){var $el;if(query.length!==0){$el=$(this);$el.data('request',(new mw.Api()).get({action:'opensearch',search:query,namespace:0,suggest:''}).done(function(data){$el.suggestions('suggestions',data[1]);}));}},cancel:function(){var apiPromise=$(this).data('request');if(apiPromise&&$.isFunction(apiPromise.abort)){apiPromise.abort();$(this).removeData('request');}},result:{render:renderFunction,select:function($input){$input.closest('form').submit();}},delay:120,highlightInput:true}).bind('paste cut drop',function(){$(this).trigger('keypress');});if($searchRegion.length===0){return;}$searchInput.suggestions({result:{render:renderFunction,select:function($input){$input.closest('form').submit();}},special:{render:specialRenderFunction,select:function($input){$input.closest('form').append($(
'<input type="hidden" name="fulltext" value="1"/>'));$input.closest('form').submit();}},$region:$searchRegion});$searchInput.data('suggestions-context').data.$container.css('fontSize',$searchInput.css('fontSize'));});}(mediaWiki,jQuery));;},{"css":[".suggestions a.mw-searchSuggest-link,.suggestions a.mw-searchSuggest-link:hover,.suggestions a.mw-searchSuggest-link:active,.suggestions a.mw-searchSuggest-link:focus{text-decoration:none;color:black}.suggestions-result-current a.mw-searchSuggest-link,.suggestions-result-current a.mw-searchSuggest-link:hover,.suggestions-result-current a.mw-searchSuggest-link:active,.suggestions-result-current a.mw-searchSuggest-link:focus{color:white}\n/* cache key: enwiki:resourceloader:filter:minify-css:7:52b1797f70c7e4094dfa4191101944e8 */"]},{"searchsuggest-search":"Search","searchsuggest-containing":"containing..."});mw.loader.implement("skins.vector.collapsibleNav",function(){(function(mw,$){'use strict';var map;function toggle($element){var
isCollapsed=$element.parent().is('.collapsed');$.cookie('vector-nav-'+$element.parent().attr('id'),isCollapsed,{'expires':30,'path':'/'});$element.parent().toggleClass('expanded').toggleClass('collapsed').find('.body').slideToggle('fast');isCollapsed=!isCollapsed;$element.find('> a').attr({'aria-pressed':isCollapsed?'false':'true','aria-expanded':isCollapsed?'false':'true'});}map={ltr:{opera:[['>=',9.6]],konqueror:[['>=',4.0]],blackberry:false,ipod:false,iphone:false,ps3:false},rtl:{opera:[['>=',9.6]],konqueror:[['>=',4.0]],blackberry:false,ipod:false,iphone:false,ps3:false}};if(!$.client.test(map)){return true;}$(function($){var $headings,tabIndex;$('#mw-panel > .portal:first').addClass('first persistent');$('#mw-panel').addClass('collapsible-nav');$('#mw-panel > .portal:not(.persistent)').each(function(i){var id=$(this).attr('id'),state=$.cookie('vector-nav-'+id);$(this).find('ul:first').attr('id',id+'-list');$(this).find('h3').wrapInner($('<a>').attr({href:'#','aria-haspopup':'true'
,'aria-controls':id+'-list',role:'button'}).click(false));if(state==='true'||(state===null&&i<1)||(state===null&&id==='p-lang')){$(this).addClass('expanded').removeClass('collapsed').find('.body').hide().show();$(this).find('h3 > a').attr({'aria-pressed':'true','aria-expanded':'true'});}else{$(this).addClass('collapsed').removeClass('expanded');$(this).find('h3 > a').attr({'aria-pressed':'false','aria-expanded':'false'});}if(state!==null){$.cookie('vector-nav-'+$(this).attr('id'),state,{'expires':30,'path':'/'});}});$headings=$('#mw-panel > .portal:not(.persistent) > h3');tabIndex=$(document).lastTabIndex()+1;$('#searchInput').attr('tabindex',tabIndex++);$headings.attr('tabindex',function(){return tabIndex++;});$('#mw-panel').delegate('.portal:not(.persistent) > h3','keydown',function(e){if(e.which===13||e.which===32){toggle($(this));}}).delegate('.portal:not(.persistent) > h3','mousedown',function(e){if(e.which!==3){toggle($(this));$(this).blur();}return false;});});}(mediaWiki,jQuery
));;},{},{"vector-collapsiblenav-more":"\u003Cvector-collapsiblenav-more\u003E"});
/* cache key: enwiki:resourceloader:filter:minify-js:7:51419821bd38dde8f0297439a59da411 */