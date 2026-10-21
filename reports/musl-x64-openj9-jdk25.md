---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-21 05:55:35 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 70-79 cores)</summary>

```
1792576324 79
1792576329 79
1792576334 79
1792576339 79
1792576344 79
1792576349 79
1792576354 79
1792576359 79
1792576364 79
1792576369 76
1792576374 76
1792576379 76
1792576384 76
1792576389 76
1792576394 76
1792576399 76
1792576404 76
1792576409 76
1792576414 76
1792576419 70
```
</details>

---

