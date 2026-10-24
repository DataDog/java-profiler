---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-24 05:55:17 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 10 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 827 |
| Sample Rate | 13.78/sec |
| Health Score | 861% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (5 unique values: 33-72 cores)</summary>

```
1792835491 72
1792835496 72
1792835501 72
1792835506 72
1792835511 37
1792835516 37
1792835521 37
1792835526 37
1792835531 37
1792835536 37
1792835541 37
1792835546 39
1792835551 39
1792835556 39
1792835561 39
1792835566 33
1792835571 33
1792835576 33
1792835581 33
1792835586 35
```
</details>

---

