---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 10:58:08 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 797 |
| Sample Rate | 13.28/sec |
| Health Score | 830% |
| Threads | 9 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1794325941 72
1794325946 74
1794325951 74
1794325956 74
1794325961 74
1794325966 74
1794325971 74
1794325976 74
1794325981 74
1794325986 74
1794325991 74
1794325996 74
1794326001 74
1794326006 74
1794326011 74
1794326016 74
1794326021 74
1794326026 74
1794326031 74
1794326036 74
```
</details>

---

