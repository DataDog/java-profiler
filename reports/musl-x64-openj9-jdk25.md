---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 08:03:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (2 unique values: 35-44 cores)</summary>

```
1794488345 35
1794488350 35
1794488355 35
1794488360 35
1794488365 35
1794488370 35
1794488375 35
1794488380 35
1794488385 35
1794488390 35
1794488395 35
1794488400 35
1794488405 35
1794488410 44
1794488415 44
1794488420 44
1794488425 44
1794488430 44
1794488435 44
1794488440 44
```
</details>

---

