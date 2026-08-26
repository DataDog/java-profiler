---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-26 09:45:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 8 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 9 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1787751617 88
1787751622 88
1787751627 88
1787751632 88
1787751637 88
1787751642 88
1787751647 88
1787751652 88
1787751657 96
1787751662 96
1787751667 96
1787751672 96
1787751677 96
1787751682 96
1787751687 96
1787751692 96
1787751697 96
1787751702 96
1787751707 96
1787751712 96
```
</details>

---

