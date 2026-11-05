---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 05:59:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 942 |
| Sample Rate | 15.70/sec |
| Health Score | 981% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1793876039 48
1793876044 48
1793876049 48
1793876054 48
1793876059 48
1793876064 48
1793876070 48
1793876075 48
1793876080 48
1793876085 48
1793876090 48
1793876095 48
1793876100 44
1793876105 44
1793876110 44
1793876115 44
1793876120 44
1793876125 44
1793876130 44
1793876135 44
```
</details>

---

