---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:10:37 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (4 unique values: 80-96 cores)</summary>

```
1789743410 80
1789743415 80
1789743420 82
1789743425 82
1789743430 82
1789743435 82
1789743440 82
1789743445 82
1789743450 82
1789743455 82
1789743460 84
1789743465 84
1789743470 84
1789743475 84
1789743480 84
1789743485 96
1789743490 96
1789743495 96
1789743500 96
1789743505 96
```
</details>

---

