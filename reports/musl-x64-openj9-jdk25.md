---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 07:25:16 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (5 unique values: 40-90 cores)</summary>

```
1794831571 70
1794831576 70
1794831581 72
1794831586 72
1794831591 72
1794831596 72
1794831601 72
1794831606 72
1794831611 72
1794831616 72
1794831621 90
1794831626 90
1794831631 57
1794831636 57
1794831641 57
1794831646 57
1794831651 57
1794831656 57
1794831661 57
1794831666 40
```
</details>

---

