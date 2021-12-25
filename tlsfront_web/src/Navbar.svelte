<script>
	let isActive=false;
</script>

<svelte:window on:resize="{() => isActive=false}"/>


<nav class="navbar is-dark has-shadow" role="navigation" aria-label="main navigation">
	<div class="navbar-brand">
		<a class="navbar-item" href="https://www.tlspack.com">
			<!-- svelte-ignore a11y-missing-attribute -->
			<img src="/assets/tlspack.png" width="32" height="32">
			&nbsp;&nbsp;&nbsp;&nbsp;
			[&nbsp;FM&nbsp;]
		</a>
		<!-- svelte-ignore a11y-missing-attribute -->
		<a role="button" class="navbar-burger" aria-label="menu" aria-expanded="false" data-target="navbarTopMenu" on:click="{() => isActive=!isActive}">
			<span aria-hidden="true"></span>
			<span aria-hidden="true"></span>
			<span aria-hidden="true"></span>
		</a>
	</div>

	<div id="navbarTopMenu" class="navbar-menu" class:is-active={isActive}>
		<div class="navbar-start">
		</div>

		<div class="navbar-end">
			<div class="navbar-item">
			</div>
		</div>
	</div>
</nav>
  