---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 04:49:20 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1042 |
| Sample Rate | 17.37/sec |
| Health Score | 1086% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1792658527 72
1792658532 72
1792658537 72
1792658542 72
1792658547 72
1792658552 72
1792658557 72
1792658562 72
1792658567 72
1792658572 72
1792658577 72
1792658582 72
1792658587 72
1792658592 72
1792658597 72
1792658602 74
1792658607 74
1792658612 74
1792658617 74
1792658622 74
```
</details>

---

