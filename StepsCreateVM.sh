#!/bin/bash

#$1 -> Name Virtual Machine
#$2 -> Size memory
#$3 -> Type OS

VM = $1
MEMORY = $2
TYPEOS = $3

VBoxManage createvm --name $VM --ostype $TYPEOS --register

VBoxManage storagectl $VM --name "SATA Controller" --add sata --controller IntelAHCI

#----------- Clonamos el disco duro --------------#
VBoxManage clonemedium disk "/home/useros/VirtualBox VMs/demo/demo-disk1.vmdk" "/home/useros/VirtualBox VMs/clone-demo/clone-demo.vdi" --format VDI

#----------- Este paso es para asginar el VDI? --------------#
VBoxManage storageattach $VM --storagectl "SATA Controller" --port 0 --device 0 --type hdd --medium "./VirtualBox VMs/clone-demo/clone-demo.vdi"

VBoxManage storagectl $VM --name "IDE Controller" --add ide

VBoxManage modifyvm $VM --ioapic on
VBoxManage modifyvm $VM --boot1 dvd --boot2 disk --boot3 none --boot4 none
VBoxManage modifyvm $VM --memory 1024 --vram 128
VBoxManage modifyvm $VM --nic1 bridged --bridgeadapter1 e1000g0
