---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-12 12:18:26 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 10 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 959 |
| Sample Rate | 15.98/sec |
| Health Score | 999% |
| Threads | 12 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (5 unique values: 78-82 cores)</summary>

```
1770916477 81
1770916482 81
1770916487 79
1770916492 79
1770916497 79
1770916502 79
1770916507 79
1770916512 79
1770916517 79
1770916522 79
1770916527 79
1770916532 79
1770916537 79
1770916542 79
1770916547 79
1770916552 79
1770916557 79
1770916562 79
1770916567 79
1770916572 82
```
</details>

---

