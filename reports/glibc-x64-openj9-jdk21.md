---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-14 12:04:47 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (6 unique values: 74-94 cores)</summary>

```
1789401537 86
1789401542 86
1789401547 86
1789401552 88
1789401557 88
1789401562 88
1789401567 88
1789401572 88
1789401577 88
1789401582 90
1789401587 90
1789401592 90
1789401597 92
1789401602 92
1789401607 94
1789401612 94
1789401617 94
1789401622 94
1789401627 94
1789401632 94
```
</details>

---

