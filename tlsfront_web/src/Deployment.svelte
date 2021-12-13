<script>
    import { onMount } from 'svelte';
    import Line from "svelte-chartjs/src/Line.svelte"

    let deployments = {};
    let data = {
        labels: [1500,1600,1700,1750,1800,1850,1900,1950,1999,2050],
        datasets: [{ 
        data: [86,114,106,106,107,111,133,221,783,2478],
        label: "Africa",
        borderColor: "#3e95cd",
        fill: true
      }, { 
        data: [282,350,411,502,635,809,947,1402,3700,5267],
        label: "Asia",
        borderColor: "#8e5ea2",
        fill: true
      }
    ]
    }

	onMount(() => {
		const interval = setInterval(() => {
		    fetch(`api/tlsfront_stats`)
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

<br/>
<br/>

<table class="table is-bordered is-striped is-narrow is-hoverable is-fullwidth has-text-left">
    <thead>
        <tr>
            <th class="svc_name"><abbr title="ServiceName">Services</abbr></th>

            <th><abbr title="tcpAcceptSuccess">TcpAccpt</abbr></th>
            <th><abbr title="sslAcceptSuccess">SSLAccpt</abbr></th>

            <th><abbr title="tcpConnInitSuccess">TcpConn</abbr></th>
            <th><abbr title="sslConnInitSuccess">SSLConn</abbr></th>

            <th><abbr title="tcpActiveConns">ActConn</abbr></th>
        </tr>
      </thead>

      <tbody>
        {#each Object.entries(deployments) as [Service, ServiceProps]}
        <tr>
            <td><strong>{Service}</strong></td>
            <td>{ServiceProps.sum[ServiceProps.sum.length-1].tcpAcceptSuccess}</td>
            <td>{ServiceProps.sum[ServiceProps.sum.length-1].sslAcceptSuccess}</td>
            <td>{ServiceProps.sum[ServiceProps.sum.length-1].tcpConnInitSuccess}</td>
            <td>{ServiceProps.sum[ServiceProps.sum.length-1].sslConnInitSuccess}</td>
            <td>{ServiceProps.sum[ServiceProps.sum.length-1].tcpActiveConns}</td>
        </tr>
    {/each}
      </tbody>
</table>

<br/>
<br/>

<Line
  data={data}
  width={50}
  height={25}
/>


<style>
    .svc_name {
        width: 170px;
        min-width: 170px;
    }
</style>