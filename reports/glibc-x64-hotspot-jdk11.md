---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 08:35:39 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 8 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (4 unique values: 80-85 cores)</summary>

```
1794490175 85
1794490180 85
1794490185 85
1794490190 85
1794490195 85
1794490200 85
1794490205 85
1794490210 85
1794490215 83
1794490220 83
1794490225 83
1794490230 83
1794490235 83
1794490240 83
1794490245 80
1794490250 80
1794490255 80
1794490260 80
1794490265 80
1794490271 80
```
</details>

---

