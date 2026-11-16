---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 07:25:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 71-77 cores)</summary>

```
1794831601 74
1794831606 74
1794831611 74
1794831616 74
1794831621 71
1794831626 71
1794831631 71
1794831636 71
1794831641 71
1794831646 71
1794831651 71
1794831656 71
1794831661 71
1794831666 71
1794831671 71
1794831676 71
1794831681 71
1794831686 71
1794831691 71
1794831696 77
```
</details>

---

