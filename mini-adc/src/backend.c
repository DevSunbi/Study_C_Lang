#include "backend.h"

#include <pthread.h>
#include <string.h>

#include "config.h"

static backend_t g_backends[BACKEND_COUNT];
static pthread_mutex_t g_backend_mutex = PTHREAD_MUTEX_INITIALIZER;
static int g_rr_index = 0;

void backend_init(void)
{
	backend_t initial[BACKED_COUNT] = {
		{1, "127.0.0.1", 9001, BACKEND_UP, 0, 0, 0, 0},
		{2, "127.0.0.1", 9002, BACKEND_UP, 0, 0, 0, 0},
		{3, "127.0.0.1", 9003, BACKEND_UP, 0, 0, 0, 0}
	};

	pthread_mutex_lock(&g_backend_mutex);
	memcpy(g_backends, initial, sizeof(g_backends));
	g_rr_index = 0;
	pthread_mutex_unlock(&g_backend_mutex);
}

const char *backend_state_string(backend_state_t state)
{
	return state == BACKEND_UP ? "UP" : "DOWN";
}

int backend_choose(backend_t *out)
{
	int found = 0;

	if(out == NULL) {
		return -1;
	}

	pthread_mutex_lock(&g_backend_mutex);

	for (int i=0; i < BACKEND_COUNT; i++) {
		int idx = (g_rr_index + i) % BACKEND_COUNT;

		if(g_backends[idx].state == BACKEND_UP) {
			g_backends[idx].active_connections++;
			g_backends[idx].total_requests++;
			*out = g_backends[idx];

			g_rr_index = (idx + 1) % BACKEND_COUNT;
			found = 1;
			break;
		}
	}
	
	pthread_mutex_unlock(&g_backend_mutex);

	return found ? 0 : -1;
}

void backend_release(int backend_id, int failed)
{
	pthread_mutex_lock(&g_backend_mutex);

	for(int i=0; i<BACKEND_COUNT; i++) {
		if(g_backends[i].id == backend_id) {
			if(g_backends[i].active_connections > 0) {
				g_backends[i].active_connections--;
			}

			if(failed) {
				g_backends[i].total_failure++;
			}
			break;
		}
	}

	pthread_mutex_unlock(&g_backend_mutex);
}

void backend_health_success(int backend_id, backend_state_t *old_state, backend_state_t *new_state)
{
	pthread_mutex_lock(&g_backend_mutex);

	for(int i=0; i < BACKEND_COUNT; i++) {
		if(g_backends[i].id == backend_id) {
			if(old_state) {
				*old_state=g_backends[i].state;
			}

			g_backends[i].fail_count = 0;
			g_backends[i].state = BACKEND_UP;

			if(new_state) {
				*new_state = g_backends[i].state;
			}
			
			break;
		}
	}

	pthread_mutex_unlock(&g_backend_mutex);
}

void backend_health_failure(int backend_id, backend_state_t *old_state, backend_sstate_t *new_state)
{
	pthread_mutex_lock(&g_backend_mutex);

	for(int i=0; i<BACKEND_COUNT; i++) {
		if(g_backends[i].id == backend_id) {
				if(old_state) {
					*old_state = g_backends[i].state;
				}

				g_backends[i].fail_count++;

				if(g_backends[i].fail_count >= HEALTH_FAIL_THRESHOLD) {
					g_backends[i].state = BACKEND_DOWN;
				}

				if(new_state) {
					*new_state = g_backends[i].state;
				}
				break;
		}
	}

	pthread_mutex_unlock(&g_backend_mutex);				
}	

int backend_get_snapshot(backend_t *out, size_t max_count)
{
	if(out == NULL || max_count == 0) {
		return 0;
	}

	pthread_mutex_lock(&g_backend_mutex);

	size_t count = max_count < BACKEND_COUNT ? max_count : BACKEND_COUNT;

	for(size_t i=0; i<count; i++) {
		out[i] = g_backends[i];
	}

	pthread_mutex_unlock(&g_backend_mutex);

	return (int)count;
}

int backend_get_by_index(size_t index, backend_t *out)
{
	if(out == NULL || index >= BACKEND_COUNT) {
		return -1;
	}

	pthread_mutex_lock(&g_backend_mutex);
	*out = g_backends[index];
	pthread_mutex_unlock(&g_backend_mutex);

	return 0;
}

void backend_get_stats(backend_stats_t *out)
{
	if(out == NULL) {
		return;
	}

	memset(out, 0, sizeof(*out));

	pthread_mutex_lock(&g_backend_mutex);

	out->total_count = BACKEND_COUNT;

	for(int i=0; i<BACKEND_COUNT; i++) {
		out->total_requests += g_backends[i].total_requests;
		out->total_failures += g_backends[i].total_failures;
		out->active_connections += g_backends[i].active_connextions;

		if(g_backends[i].state == BACKEND_UP) {
			out->up_count++;
		}
	}

	pthread_mutex_unlock(&g_backend_mutex);
}
