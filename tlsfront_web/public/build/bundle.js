var app=function(){"use strict";function t(){}function n(t){return t()}function e(){return Object.create(null)}function r(t){t.forEach(n)}function a(t){return"function"==typeof t}function o(t,n){return t!=t?n==n:t!==n||t&&"object"==typeof t||"function"==typeof t}function i(t,n){t.appendChild(n)}function s(t,n,e){t.insertBefore(n,e||null)}function c(t){t.parentNode.removeChild(t)}function u(t){return document.createElement(t)}function l(){return t=" ",document.createTextNode(t);var t}function d(t,n,e,r){return t.addEventListener(n,e,r),()=>t.removeEventListener(n,e,r)}function f(t,n,e){null==e?t.removeAttribute(n):t.getAttribute(n)!==e&&t.setAttribute(n,e)}function p(t,n,e){t.classList[e?"add":"remove"](n)}let g;function m(t){g=t}const h=[],$=[],b=[],v=[],y=Promise.resolve();let _=!1;function x(t){b.push(t)}let w=!1;const k=new Set;function E(){if(!w){w=!0;do{for(let t=0;t<h.length;t+=1){const n=h[t];m(n),L(n.$$)}for(m(null),h.length=0;$.length;)$.pop()();for(let t=0;t<b.length;t+=1){const n=b[t];k.has(n)||(k.add(n),n())}b.length=0}while(h.length);for(;v.length;)v.pop()();_=!1,w=!1,k.clear()}}function L(t){if(null!==t.fragment){t.update(),r(t.before_update);const n=t.dirty;t.dirty=[-1],t.fragment&&t.fragment.p(t.ctx,n),t.after_update.forEach(x)}}const M=new Set;function T(t,n){t&&t.i&&(M.delete(t),t.i(n))}function A(t,e,o,i){const{fragment:s,on_mount:c,on_destroy:u,after_update:l}=t.$$;s&&s.m(e,o),i||x((()=>{const e=c.map(n).filter(a);u?u.push(...e):r(e),t.$$.on_mount=[]})),l.forEach(x)}function j(t,n){const e=t.$$;null!==e.fragment&&(r(e.on_destroy),e.fragment&&e.fragment.d(n),e.on_destroy=e.fragment=null,e.ctx=[])}function H(t,n){-1===t.$$.dirty[0]&&(h.push(t),_||(_=!0,y.then(E)),t.$$.dirty.fill(0)),t.$$.dirty[n/31|0]|=1<<n%31}function N(n,a,o,i,s,u,l,d=[-1]){const f=g;m(n);const p=n.$$={fragment:null,ctx:null,props:u,update:t,not_equal:s,bound:e(),on_mount:[],on_destroy:[],on_disconnect:[],before_update:[],after_update:[],context:new Map(a.context||(f?f.$$.context:[])),callbacks:e(),dirty:d,skip_bound:!1,root:a.target||f.$$.root};l&&l(p.root);let h=!1;if(p.ctx=o?o(n,a.props||{},((t,e,...r)=>{const a=r.length?r[0]:e;return p.ctx&&s(p.ctx[t],p.ctx[t]=a)&&(!p.skip_bound&&p.bound[t]&&p.bound[t](a),h&&H(n,t)),e})):[],p.update(),h=!0,r(p.before_update),p.fragment=!!i&&i(p.ctx),a.target){if(a.hydrate){const t=function(t){return Array.from(t.childNodes)}(a.target);p.fragment&&p.fragment.l(t),t.forEach(c)}else p.fragment&&p.fragment.c();a.intro&&T(n.$$.fragment),A(n,a.target,a.anchor,a.customElement),E()}m(f)}class O{$destroy(){j(this,1),this.$destroy=t}$on(t,n){const e=this.$$.callbacks[t]||(this.$$.callbacks[t]=[]);return e.push(n),()=>{const t=e.indexOf(n);-1!==t&&e.splice(t,1)}}$set(t){var n;this.$$set&&(n=t,0!==Object.keys(n).length)&&(this.$$.skip_bound=!0,this.$$set(t),this.$$.skip_bound=!1)}}function S(n){let e,a,o,g,m,h,$,b,v;return{c(){e=u("nav"),a=u("div"),o=u("a"),o.innerHTML='<img src="/assets/gigamon.png" width="32" height="32"/>',g=l(),m=u("a"),m.innerHTML='<span aria-hidden="true"></span> \n\t\t\t<span aria-hidden="true"></span> \n\t\t\t<span aria-hidden="true"></span>',h=l(),$=u("div"),$.innerHTML='<div class="navbar-start"></div> \n\n\t\t<div class="navbar-end"><div class="navbar-item"><div class="buttons"><a class="button is-primary"><strong>Sign up</strong></a> \n\t\t\t\t  \n\t\t\t\t  <a class="button is-light">Log in</a></div></div></div>',f(o,"class","navbar-item"),f(o,"href","https://www.gigamon.com"),f(m,"role","button"),f(m,"class","navbar-burger"),f(m,"aria-label","menu"),f(m,"aria-expanded","false"),f(m,"data-target","navbarTopMenu"),f(a,"class","navbar-brand"),f($,"id","navbarTopMenu"),f($,"class","navbar-menu"),p($,"is-active",n[0]),f(e,"class","navbar is-dark is-fixed-top"),f(e,"role","navigation"),f(e,"aria-label","main navigation")},m(t,r){s(t,e,r),i(e,a),i(a,o),i(a,g),i(a,m),i(e,h),i(e,$),b||(v=[d(window,"resize",n[1]),d(m,"click",n[2])],b=!0)},p(t,[n]){1&n&&p($,"is-active",t[0])},i:t,o:t,d(t){t&&c(e),b=!1,r(v)}}}function C(t,n,e){let r=!1;return[r,()=>e(0,r=!1),()=>e(0,r=!r)]}class q extends O{constructor(t){super(),N(this,t,C,S,o,{})}}function z(n){let e,r,a;return r=new q({}),{c(){var t;e=u("main"),(t=r.$$.fragment)&&t.c(),f(e,"class","svelte-1h6otfa")},m(t,n){s(t,e,n),A(r,e,null),a=!0},p:t,i(t){a||(T(r.$$.fragment,t),a=!0)},o(t){!function(t,n,e,r){if(t&&t.o){if(M.has(t))return;M.add(t),(void 0).c.push((()=>{M.delete(t),r&&(e&&t.d(1),r())})),t.o(n)}}(r.$$.fragment,t),a=!1},d(t){t&&c(e),j(r)}}}return new class extends O{constructor(t){super(),N(this,t,null,z,o,{})}}({target:document.body,props:{name:"world"}})}();
//# sourceMappingURL=bundle.js.map