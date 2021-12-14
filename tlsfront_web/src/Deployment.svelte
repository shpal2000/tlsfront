<script>
  import { onMount } from 'svelte';
  import Chart from 'chart.js/auto';

  let deployments = {};

  let chartValues = [];
	let chartLabels = [];
	let ctx;
	let chartCanvas;
  let chart;
  let data = {
						labels: chartLabels,
						datasets: [{
								label: '',
								backgroundColor: 'rgb(255, 99, 132)',
								borderColor: 'rgb(255, 99, 132)',
								data: chartValues
						}]
			};

	onMount(() => {
    ctx = chartCanvas.getContext('2d');
    chart = new Chart(ctx, {
				type: 'line',
				data: data,
        options: {
          animation :{
            duration: 0
          },
          interaction: {
            intersect: false
          },
          plugins: {
            legend: false
          },
          scales: {
            x: {
              type: 'linear'
            }
          }
        }
		});

		const interval = setInterval(() => {
		    fetch(`api/tlsfront_stats`)
                .then((response) => response.json())
                .then((results) => {
                    deployments = results;
                    data.labels = [...Array(10).keys()];
                    data.datasets= Object.keys(deployments).map(k => ({
                                    label: k,
                                    fill: true,
                                    borderColor: "#ffa700",
                                    backgroundColor: "#fafad2",
                                    data: deployments[k].sum.map(v => v.tlsfrontThroughput)
                                  }));
                    chart.update();
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

<canvas bind:this={chartCanvas} id="myChart"></canvas>


<style>
    .svc_name {
        width: 170px;
        min-width: 170px;
    }
</style>