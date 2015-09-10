#!/bin/bash

AGGREGATOR=${AGGREGATOR:-./aggregator_cut}
TOP=${TOP:-10}
KEEP=${KEEP:-10}
MAX=${MAX:-1000}
INPUT=${INPUT:-input2} #2015-09-08-04-10-00.csv
OUTPUT=${OUTPUT:-out}

PARAMS="$TOP $KEEP $MAX"

declare -A MAPPING

MAPPING["src_ip"]="3"
MAPPING["src_port"]="4" 
MAPPING["dest_ip"]="5"
MAPPING["dest_port"]="6" 
MAPPING["protocol"]="7" 
MAPPING["exporter"]="14" 
MAPPING["interface_in"]="15" 
MAPPING["interface_out"]="16"

mkdir -p $OUTPUT

aggreagate_flows_packets_bytes() {
    tee >($AGGREGATOR ${MAPPING[$1]} 10 $PARAMS > ${OUTPUT}/$1_flows) \
	>($AGGREGATOR ${MAPPING[$1]} 11 $PARAMS > ${OUTPUT}/$1_packets) \
	>($AGGREGATOR ${MAPPING[$1]} 12 $PARAMS > ${OUTPUT}/$1_bytes)
}

cat $INPUT | \
    aggreagate_flows_packets_bytes src_ip | \
    aggreagate_flows_packets_bytes src_port | \
    aggreagate_flows_packets_bytes dest_ip | \
    aggreagate_flows_packets_bytes dest_port | \
    aggreagate_flows_packets_bytes protocol | \
    aggreagate_flows_packets_bytes exporter | \
    aggreagate_flows_packets_bytes interface_in | \
    aggreagate_flows_packets_bytes interface_out &> /dev/null

