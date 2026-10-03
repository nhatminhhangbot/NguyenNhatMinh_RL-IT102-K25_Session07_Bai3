#include <stdio.h>
#include <math.h>

struct DeviceUnoptimized {
    char status;           
    float voltage;         
    char device_id;        
    float current;         
    double measured_power;
    float time_min;        
};

struct ElectricalParams {
    double measured_power; 
    float voltage;         
    float current;         
};

struct OperationalParams {
    float time_min;        
    char status;           
    char device_id;        
};

struct DeviceNestedOptimized {
    struct ElectricalParams elec;
    struct OperationalParams op;
};

int main() {
    printf("=== SO SANH KICH THUOC BO NHO (sizeof) ===\n");
    printf("Struct chua toi uu : %zu bytes\n", sizeof(struct DeviceUnoptimized));
    printf("Struct toi uu (Nested): %zu bytes\n", sizeof(struct DeviceNestedOptimized));
    printf("-----------------------------------------\n\n");

    struct DeviceNestedOptimized device;

    printf("=== NHAP THONG SO THIET BI IOT GATEWAY ===\n");
    printf("Nhap trang thai (0: Tat, 1: Bat): ");
    if (scanf("%d", (int*)&device.op.status) != 1) {
    	return 0;
	} 

    printf("Nhap dien ap U (Volt): ");
    if (scanf("%f", &device.elec.voltage) != 1) {
    	return 0;
	}

    printf("Nhap dong dien I (Ampere): ");
    if (scanf("%f", &device.elec.current) != 1) {
    	return 0;
	}

    printf("Nhap cong suat do thuc te P (Watt): ");
    if (scanf("%lf", &device.elec.measured_power) != 1) {
    	return 0;
	}

    printf("Nhap thoi gian hoat dong t (phut): ");
    if (scanf("%f", &device.op.time_min) != 1) {
    	return 0;
	}

    if (device.elec.voltage <= 0.0f) {
        printf("[LOI] Dien ap U phai lon hon 0!\n");
        return 0;
    }
    if (device.elec.current < 0.0f) {
        printf("[LOI] Dong dien I khong duoc am!\n");
        return 0;
    }
    if (device.op.time_min < 0.0f) {
        printf("[LOI] Thoi gian hoat dong t khong duoc am!\n");
        return 0;
    }
    if (device.op.status != 0 && device.op.status != 1) {
        printf("[LOI] Trang thai status chi nhan gia tri 0 hoac 1!\n");
        return 0;
    }

    printf("\n=== KET QUA KIEM TRA AN TOAN & NGHIEP VU ===\n");

    double p_calc = (double)device.elec.voltage * (double)device.elec.current;

    double deviation = fabs(device.elec.measured_power - p_calc);
    if (deviation > (0.05 * p_calc)) {
        printf("[CANH BAO] Cam bien cong suat bao sai lech! (P_do: %.2fW, P_calc: %.2fW)\n", 
               device.elec.measured_power, p_calc);
    } else {
        printf("[OK] Cam bien cong suat hoat dong chinh xac.\n");
    }

    if (device.elec.current > 30.0f || device.elec.measured_power > 6600.0) {
        printf("[CANH BAO NGUY HIEM] QUA TAI NGUY HIEM! (I = %.2fA, P = %.2fW)\n", 
               device.elec.current, device.elec.measured_power);
    }

    if (device.op.status == 0 && device.elec.current > 0.05f) {
        printf("[CANH BAO AN TOAN] RO RI DIEN HOAC TAI AN! (Status = OFF nhung I = %.3fA)\n", 
               device.elec.current);
    }

    double kWh = (device.elec.measured_power * ((double)device.op.time_min / 60.0)) / 1000.0;
    printf("[THONG TIN] Dien nang tieu thu: %.4f kWh\n", kWh);

    return 0;
}
