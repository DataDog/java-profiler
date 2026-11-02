---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 05:56:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 10 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1793616701 30
1793616706 30
1793616711 30
1793616716 28
1793616721 28
1793616726 28
1793616731 28
1793616736 28
1793616741 28
1793616746 28
1793616751 28
1793616756 28
1793616761 28
1793616766 28
1793616771 28
1793616776 28
1793616781 28
1793616786 28
1793616791 28
1793616796 28
```
</details>

---

