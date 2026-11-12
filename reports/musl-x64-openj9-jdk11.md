---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:57:36 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 82-88 cores)</summary>

```
1794498738 82
1794498743 82
1794498748 82
1794498753 82
1794498758 82
1794498763 82
1794498768 82
1794498773 82
1794498778 82
1794498783 82
1794498788 84
1794498793 84
1794498798 84
1794498803 84
1794498808 84
1794498813 86
1794498818 86
1794498823 88
1794498829 88
1794498834 86
```
</details>

---

