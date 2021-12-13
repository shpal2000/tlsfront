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
        fill: false
      }, { 
        data: [282,350,411,502,635,809,947,1402,3700,5267],
        label: "Asia",
        borderColor: "#8e5ea2",
        fill: false
      }, { 
        data: [168,170,178,190,203,276,408,547,675,734],
        label: "Europe",
        borderColor: "#3cba9f",
        fill: false
      }, { 
        data: [40,20,10,16,24,38,74,167,508,784],
        label: "Latin America",
        borderColor: "#e8c3b9",
        fill: false
      }, { 
        data: [6,3,2,2,7,26,82,172,312,433],
        label: "North America",
        borderColor: "#c45850",
        fill: false
      }
    ]
    }

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