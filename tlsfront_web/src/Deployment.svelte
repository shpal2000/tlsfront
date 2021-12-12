<script>
	async function getDeployments() {
		const res = await fetch(`api/stats`);
		const results = await res.json();

		if (res.ok) {
			return results;
		} else {
			return {};
		}
	}

    let promise = getDeployments();


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
            {#await promise}
                <p>...waiting</p>
            {:then deployments}
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
            {/await}
      </tbody>
</table>


<style>
    .svc_name {
        width: 170px;
        min-width: 170px;
    }
</style>