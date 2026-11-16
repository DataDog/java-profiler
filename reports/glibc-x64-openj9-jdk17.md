---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 07:25:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 72-94 cores)</summary>

```
1794831586 72
1794831591 72
1794831596 72
1794831601 72
1794831606 72
1794831611 72
1794831616 72
1794831621 72
1794831626 72
1794831631 72
1794831636 72
1794831641 72
1794831646 94
1794831651 94
1794831656 94
1794831661 94
1794831666 94
1794831671 94
1794831676 94
1794831681 94
```
</details>

---

