<script>
  import { onMount } from 'svelte';
  import Chart from 'chart.js/auto';

  let deployments = {};

  let chartValues = [20, 10, 5, 2, 20, 30, 45];
	let chartLabels = ['January', 'February', 'March', 'April', 'May', 'June', 'July'];
	let ctx;
	let chartCanvas;
  let chart;
  let data = {
						labels: chartLabels,
						datasets: [{
								label: 'Revenue',
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
                    data.labels = [1,2,3];
                    data.datasets= Object.keys(deployments).map(k => ({
                                    label: k,
                                    fill: true,
                                    borderColor: "#3e95cd",
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

<canvas bind:this={chartCanvas} id="myChart"></canvas>


<style>
    .svc_name {
        width: 170px;
        min-width: 170px;
    }
</style>