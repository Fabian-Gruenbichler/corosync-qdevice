/*
 * Copyright (c) 2015-2020 Red Hat, Inc.
 *
 * All rights reserved.
 *
 * Author: Jan Friesse (jfriesse@redhat.com)
 *
 * This software licensed under BSD license, the text of which follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the Red Hat, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/types.h>

#include "log.h"
#include "qnet-config.h"
#include "qdevice-net-algorithm.h"

#include "qdevice-net-algo-test.h"
#include "qdevice-net-algo-ffsplit.h"
#include "qdevice-net-algo-2nodelms.h"
#include "qdevice-net-algo-lms.h"

static struct qdevice_net_algorithm *qdevice_net_algorithm_array[QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE];

int
qdevice_net_algorithm_init(struct qdevice_net_instance *instance)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_init unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->init(instance));
}

int
qdevice_net_algorithm_connected(struct qdevice_net_instance *instance, enum tlv_heuristics *heuristics,
    int *send_config_node_list, int *send_membership_node_list, int *send_quorum_node_list, enum tlv_vote *vote)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_connected unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->connected(instance,
	    heuristics, send_config_node_list, send_membership_node_list, send_quorum_node_list, vote));
}

int
qdevice_net_algorithm_config_node_list_changed(struct qdevice_net_instance *instance,
    const struct node_list *nlist, int config_version_set, uint64_t config_version,
    int *send_node_list, enum tlv_vote *vote)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_connected unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->
	    config_node_list_changed(instance, nlist, config_version_set, config_version,
	    send_node_list, vote));
}

int
qdevice_net_algorithm_votequorum_node_list_notify(struct qdevice_net_instance *instance,
    const struct tlv_ring_id *ring_id, uint32_t node_list_entries, uint32_t node_list[],
    int *pause_cast_vote_timer, enum tlv_vote *vote)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_votequorum_node_list_notify "
		    "unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->votequorum_node_list_notify(
	    instance, ring_id, node_list_entries, node_list, pause_cast_vote_timer, vote));
}

int
qdevice_net_algorithm_votequorum_node_list_heuristics_notify(struct qdevice_net_instance *instance,
    const struct tlv_ring_id *ring_id, uint32_t node_list_entries, uint32_t node_list[],
    int *send_node_list, enum tlv_vote *vote, enum tlv_heuristics *heuristics)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_votequorum_node_list_heuristics_notify "
		    "unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->
	    votequorum_node_list_heuristics_notify(
	    instance, ring_id, node_list_entries, node_list, send_node_list, vote, heuristics));
}

int
qdevice_net_algorithm_votequorum_quorum_notify(struct qdevice_net_instance *instance,
    uint32_t quorate, uint32_t node_list_entries, votequorum_node_t node_list[], int *send_node_list,
    enum tlv_vote *vote)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_votequorum_quorum_notify "
		    "unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->
	    votequorum_quorum_notify(instance, quorate, node_list_entries, node_list,
	    send_node_list, vote));
}

int
qdevice_net_algorithm_votequorum_expected_votes_notify(struct qdevice_net_instance *instance,
    uint32_t expected_votes, enum tlv_vote *vote)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_votequorum_expected_votes_notify "
		    "unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->
	    votequorum_expected_votes_notify(instance, expected_votes, vote));
}

int
qdevice_net_algorithm_config_node_list_reply_received(struct qdevice_net_instance *instance,
    uint32_t seq_number, int initial, const struct tlv_ring_id *ring_id, int ring_id_is_valid,
    enum tlv_vote *vote)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_config_node_list_reply_received "
		    "unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->
	    config_node_list_reply_received(instance, seq_number, initial, ring_id,
	    ring_id_is_valid, vote));
}

int
qdevice_net_algorithm_membership_node_list_reply_received(struct qdevice_net_instance *instance,
    uint32_t seq_number, const struct tlv_ring_id *ring_id, int ring_id_is_valid, enum tlv_vote *vote)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_membership_node_list_reply_received "
		    "unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->
	    membership_node_list_reply_received(instance, seq_number, ring_id, ring_id_is_valid,
	    vote));
}

int
qdevice_net_algorithm_quorum_node_list_reply_received(struct qdevice_net_instance *instance,
    uint32_t seq_number, const struct tlv_ring_id *ring_id, int ring_id_is_valid,
    enum tlv_vote *vote)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_quorum_node_list_reply_received "
		    "unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->
	    quorum_node_list_reply_received(instance, seq_number, ring_id, ring_id_is_valid,
	    vote));
}

int
qdevice_net_algorithm_ask_for_vote_reply_received(struct qdevice_net_instance *instance,
    uint32_t seq_number, const struct tlv_ring_id *ring_id, int ring_id_is_valid,
    enum tlv_vote *vote)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_ask_for_vote_reply_received "
		    "unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->
	    ask_for_vote_reply_received(instance, seq_number, ring_id, ring_id_is_valid, vote));
}

int
qdevice_net_algorithm_vote_info_received(struct qdevice_net_instance *instance,
    uint32_t seq_number, const struct tlv_ring_id *ring_id, int ring_id_is_valid,
    enum tlv_vote *vote)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_vote_info_received "
		    "unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->
	    vote_info_received(instance, seq_number, ring_id, ring_id_is_valid, vote));
}

int
qdevice_net_algorithm_echo_reply_received(struct qdevice_net_instance *instance,
    uint32_t seq_number, int is_expected_seq_number)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_echo_reply_received "
		    "unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->
	    echo_reply_received(instance, seq_number, is_expected_seq_number));
}

int
qdevice_net_algorithm_echo_reply_not_received(struct qdevice_net_instance *instance)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_echo_reply_not_received "
		    "unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->
	    echo_reply_not_received(instance));
}

int
qdevice_net_algorithm_heuristics_change(struct qdevice_net_instance *instance,
    enum tlv_heuristics *heuristics, int *send_msg, enum tlv_vote *vote)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_heuristics_change "
		    "unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->
	    heuristics_change(instance, heuristics, send_msg, vote));
}

int
qdevice_net_algorithm_heuristics_change_reply_received(struct qdevice_net_instance *instance,
    uint32_t seq_number, const struct tlv_ring_id *ring_id, int ring_id_is_valid,
    enum tlv_heuristics heuristics, enum tlv_vote *vote)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_heuristics_change_reply_received "
		    "unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->
	    heuristics_change_reply_received(instance, seq_number, ring_id, ring_id_is_valid,
	    heuristics, vote));
}

int
qdevice_net_algorithm_disconnected(struct qdevice_net_instance *instance,
    enum qdevice_net_disconnect_reason disconnect_reason, int *try_reconnect, enum tlv_vote *vote)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_disconnected "
		    "unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->
	    disconnected(instance, disconnect_reason, try_reconnect, vote));
}

void
qdevice_net_algorithm_destroy(struct qdevice_net_instance *instance)
{

	if (instance->decision_algorithm >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE ||
	    qdevice_net_algorithm_array[instance->decision_algorithm] == NULL) {
		log(LOG_CRIT, "qdevice_net_algorithm_destroy "
		    "unhandled decision algorithm");
		exit(EXIT_FAILURE);
	}

	return (qdevice_net_algorithm_array[instance->decision_algorithm]->
	    destroy(instance));
}

int
qdevice_net_algorithm_register(enum tlv_decision_algorithm_type algorithm_number,
    struct qdevice_net_algorithm *algorithm)
{

	if (algorithm_number >= QDEVICE_NET_STATIC_SUPPORTED_DECISION_ALGORITHMS_SIZE) {
		return (-1);
	}

	if (qdevice_net_algorithm_array[algorithm_number] != NULL) {
		return (-1);
	}

	qdevice_net_algorithm_array[algorithm_number] = algorithm;

	return (0);
}

int
qdevice_net_algorithm_register_all(void)
{

	if (qdevice_net_algo_test_register() != 0) {
		log(LOG_CRIT, "Failed to register decision algorithm 'test' ");
		return (-1);
	}

	if (qdevice_net_algo_ffsplit_register() != 0) {
		log(LOG_CRIT, "Failed to register decision algorithm 'ffsplit' ");
		return (-1);
	}

	if (qdevice_net_algo_2nodelms_register() != 0) {
		log(LOG_CRIT, "Failed to register decision algorithm '2nodelms' ");
		return (-1);
	}

	if (qdevice_net_algo_lms_register() != 0) {
		log(LOG_CRIT, "Failed to register decision algorithm 'lms' ");
		return (-1);
	}

	return (0);
}
