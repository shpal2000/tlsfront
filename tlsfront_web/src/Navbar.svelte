<script>
	let isActive=false;
</script>

<svelte:window on:resize="{() => isActive=false}"/>

<nav class="navbar is-dark is-fixed-top" role="navigation" aria-label="main navigation">
	<div class="navbar-brand">
		<a class="navbar-item" href="https://www.gigamon.com">
			<!-- svelte-ignore a11y-missing-attribute -->
			<img src="/assets/gigamon.png" width="32" height="32">
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
				<div class="buttons">
				  <!-- svelte-ignore a11y-missing-attribute -->
				  <a class="button is-primary">
					<strong>Sign up</strong>
				  </a>
				  <!-- svelte-ignore a11y-missing-attribute -->
				  <a class="button is-light">
					Log in
				  </a>
				</div>
			</div>
		</div>
	</div>
</nav>
  