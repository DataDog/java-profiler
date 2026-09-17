---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 10:30:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (5 unique values: 67-96 cores)</summary>

```
1789655028 70
1789655033 70
1789655038 70
1789655043 70
1789655048 78
1789655053 78
1789655058 95
1789655063 95
1789655068 95
1789655074 96
1789655079 96
1789655084 96
1789655089 96
1789655094 67
1789655099 67
1789655104 67
1789655109 67
1789655114 67
1789655119 67
1789655124 67
```
</details>

---

