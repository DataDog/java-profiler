---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-06 13:00:30 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 8 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1772819708 27
1772819713 27
1772819718 27
1772819723 27
1772819728 27
1772819733 27
1772819738 27
1772819743 27
1772819748 27
1772819753 27
1772819758 27
1772819763 27
1772819768 27
1772819773 27
1772819778 27
1772819783 27
1772819788 27
1772819793 27
1772819798 32
1772819803 32
```
</details>

---

