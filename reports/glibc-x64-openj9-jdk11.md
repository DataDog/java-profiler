---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-11 11:58:27 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 823 |
| Sample Rate | 13.72/sec |
| Health Score | 857% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (7 unique values: 60-76 cores)</summary>

```
1770828687 65
1770828692 65
1770828697 65
1770828702 65
1770828707 65
1770828712 65
1770828717 60
1770828722 60
1770828727 60
1770828733 60
1770828738 60
1770828743 61
1770828748 61
1770828753 63
1770828758 63
1770828763 65
1770828768 65
1770828773 65
1770828778 67
1770828783 67
```
</details>

---

