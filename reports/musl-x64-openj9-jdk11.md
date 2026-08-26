---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-26 09:45:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 941 |
| Sample Rate | 15.68/sec |
| Health Score | 980% |
| Threads | 12 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 82-94 cores)</summary>

```
1787751617 84
1787751622 82
1787751627 82
1787751632 82
1787751637 82
1787751642 82
1787751647 82
1787751652 82
1787751657 82
1787751662 82
1787751667 82
1787751672 82
1787751677 92
1787751682 92
1787751687 92
1787751692 92
1787751697 94
1787751702 94
1787751707 94
1787751712 94
```
</details>

---

