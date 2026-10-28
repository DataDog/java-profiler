---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 12:39:35 EDT

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
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 11 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (4 unique values: 48-64 cores)</summary>

```
1793205325 48
1793205330 48
1793205335 48
1793205340 53
1793205345 53
1793205350 53
1793205355 53
1793205360 53
1793205365 53
1793205370 64
1793205375 64
1793205380 64
1793205385 64
1793205390 64
1793205395 64
1793205400 64
1793205405 64
1793205410 51
1793205415 51
1793205420 51
```
</details>

---

