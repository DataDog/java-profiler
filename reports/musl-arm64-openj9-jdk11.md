---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 07:24:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 14 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1794831571 33
1794831576 33
1794831581 33
1794831586 33
1794831591 33
1794831596 33
1794831601 33
1794831606 33
1794831611 33
1794831616 33
1794831621 33
1794831626 33
1794831631 33
1794831636 33
1794831641 38
1794831646 38
1794831651 38
1794831656 38
1794831661 38
1794831666 38
```
</details>

---

