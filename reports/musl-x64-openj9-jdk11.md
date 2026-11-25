---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 06:18:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 9 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (2 unique values: 70-74 cores)</summary>

```
1795605045 70
1795605050 70
1795605055 70
1795605060 70
1795605065 70
1795605070 70
1795605075 74
1795605080 74
1795605085 74
1795605090 74
1795605095 74
1795605100 74
1795605105 74
1795605110 74
1795605115 74
1795605120 74
1795605125 74
1795605130 74
1795605135 74
1795605140 74
```
</details>

---

