---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 14:23:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 7 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (3 unique values: 60-64 cores)</summary>

```
1795634345 60
1795634350 60
1795634355 60
1795634360 60
1795634365 60
1795634370 60
1795634375 60
1795634380 60
1795634385 62
1795634390 62
1795634395 62
1795634400 62
1795634405 62
1795634410 62
1795634415 64
1795634420 64
1795634425 64
1795634430 62
1795634435 62
1795634440 62
```
</details>

---

