---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-11 10:11:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 8 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 945 |
| Sample Rate | 15.75/sec |
| Health Score | 984% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 87-92 cores)</summary>

```
1786457235 90
1786457240 92
1786457245 92
1786457250 92
1786457255 92
1786457260 92
1786457265 92
1786457270 92
1786457275 92
1786457280 92
1786457285 92
1786457290 92
1786457295 92
1786457300 92
1786457305 89
1786457310 89
1786457315 89
1786457320 89
1786457325 89
1786457330 89
```
</details>

---

