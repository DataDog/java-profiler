---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 19:49:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 71-79 cores)</summary>

```
1794789920 79
1794789925 79
1794789930 79
1794789935 79
1794789940 79
1794789945 79
1794789950 79
1794789955 71
1794789960 71
1794789965 71
1794789970 71
1794789975 73
1794789980 73
1794789985 73
1794789990 73
1794789995 73
1794790000 73
1794790005 73
1794790010 73
1794790015 73
```
</details>

---

