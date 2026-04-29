---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-29 11:09:02 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 395 |
| Sample Rate | 6.58/sec |
| Health Score | 411% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 79-84 cores)</summary>

```
1777475043 81
1777475048 81
1777475053 81
1777475058 81
1777475063 83
1777475068 83
1777475073 83
1777475078 83
1777475083 83
1777475088 83
1777475093 83
1777475098 83
1777475103 83
1777475108 83
1777475113 83
1777475118 83
1777475123 83
1777475128 83
1777475133 83
1777475139 83
```
</details>

---

