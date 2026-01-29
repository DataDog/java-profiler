---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-29 09:48:27 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 887 |
| Sample Rate | 29.57/sec |
| Health Score | 1848% |
| Threads | 12 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1258 |
| Sample Rate | 41.93/sec |
| Health Score | 2621% |
| Threads | 12 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (5 unique values: 59-78 cores)</summary>

```
1769697758 78
1769697763 74
1769697768 74
1769697773 74
1769697778 64
1769697783 64
1769697788 64
1769697793 64
1769697798 64
1769697803 64
1769697808 64
1769697813 64
1769697818 64
1769697823 64
1769697828 64
1769697833 64
1769697838 64
1769697843 61
1769697849 61
1769697854 61
```
</details>

---

