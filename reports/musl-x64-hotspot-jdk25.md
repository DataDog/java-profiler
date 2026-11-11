---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 15:16:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (6 unique values: 58-71 cores)</summary>

```
1794427931 58
1794427936 58
1794427941 61
1794427946 61
1794427951 61
1794427956 63
1794427961 63
1794427966 60
1794427971 60
1794427976 60
1794427981 60
1794427986 60
1794427991 60
1794427996 60
1794428001 60
1794428006 60
1794428011 60
1794428016 69
1794428021 69
1794428026 69
```
</details>

---

