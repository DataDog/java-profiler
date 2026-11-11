---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 16:53:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 795 |
| Sample Rate | 13.25/sec |
| Health Score | 828% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (6 unique values: 70-76 cores)</summary>

```
1794433719 73
1794433724 73
1794433729 73
1794433734 75
1794433739 75
1794433744 75
1794433749 75
1794433754 75
1794433759 75
1794433765 75
1794433770 75
1794433775 75
1794433780 75
1794433785 75
1794433790 75
1794433795 75
1794433800 74
1794433805 74
1794433810 76
1794433815 76
```
</details>

---

