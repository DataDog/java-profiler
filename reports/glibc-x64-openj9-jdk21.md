---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 07:25:14 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 84-96 cores)</summary>

```
1794831581 94
1794831586 94
1794831591 94
1794831596 94
1794831601 96
1794831606 96
1794831611 94
1794831616 94
1794831621 94
1794831626 94
1794831631 94
1794831636 94
1794831641 94
1794831646 94
1794831651 94
1794831656 92
1794831661 92
1794831666 92
1794831671 92
1794831676 92
```
</details>

---

