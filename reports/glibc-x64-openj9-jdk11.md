---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 12:40:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 57-60 cores)</summary>

```
1792687005 60
1792687010 60
1792687015 60
1792687020 60
1792687025 60
1792687030 60
1792687035 60
1792687040 60
1792687045 60
1792687050 60
1792687055 60
1792687060 60
1792687065 60
1792687070 60
1792687075 57
1792687080 57
1792687085 57
1792687090 57
1792687095 57
1792687100 57
```
</details>

---

