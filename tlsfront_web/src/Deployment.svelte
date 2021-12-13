<script>
    import { onMount } from 'svelte';

    let deployments = {};

	onMount(() => {
		const interval = setInterval(() => {
		    fetch(`api/stats`)
                .then((response) => response.json())
                .then((results) => {
                    deployments = results;
                });
		}, 1000);

		return () => {
			clearInterval(interval);
		};
	});

</script>


<table class="table is-bordered is-striped is-narrow is-hoverable is-fullwidth has-text-left">
    <thead>
        <tr>
            <th class="svc_name"><abbr title="ServiceName">Services</abbr></th>

            <th><abbr title="tcpAcceptSuccess">TcpAccpt</abbr></th>
            <th><abbr title="sslAcceptSuccess">SSLAccpt</abbr></th>

            <th><abbr title="tcpConnInitSuccess">TcpConn</abbr></th>
            <th><abbr title="sslConnInitSuccess">SSLConn</abbr></th>

            <th><abbr title="tcpActiveConns">ActConn</abbr></th>

            <th><abbr title="Throughput">Thpt</abbr></th>
        </tr>
      </thead>

      <tbody>
        {#each Object.entries(deployments) as [Service, ServiceProps]}
        <tr>
            <td>{Service}</td>
            <td>{ServiceProps.sum.tcpAcceptSuccess}</td>
            <td>{ServiceProps.sum.sslAcceptSuccess}</td>
            <td>{ServiceProps.sum.tcpConnInitSuccess}</td>
            <td>{ServiceProps.sum.sslConnInitSuccess}</td>
            <td>{ServiceProps.sum.tcpActiveConns}</td>
            <td>show</td>
        </tr>
    {/each}
      </tbody>
</table>


<style>
    .svc_name {
        width: 170px;
        min-width: 170px;
    }
</style>