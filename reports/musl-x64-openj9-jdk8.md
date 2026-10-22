---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-22 12:39:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 57-65 cores)</summary>

```
1792686769 65
1792686774 57
1792686779 57
1792686784 59
1792686789 59
1792686795 59
1792686800 59
1792686805 61
1792686810 61
1792686815 61
1792686820 61
1792686825 61
1792686830 63
1792686835 63
1792686840 63
1792686845 63
1792686850 63
1792686855 63
1792686860 63
1792686865 63
```
</details>

---

