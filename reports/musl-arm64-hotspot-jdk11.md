---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 10:42:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 301 |
| Sample Rate | 5.02/sec |
| Health Score | 314% |
| Threads | 10 |
| Allocations | 189 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 13 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794324984 43
1794324989 43
1794324994 43
1794324999 43
1794325004 43
1794325009 43
1794325014 43
1794325019 43
1794325024 43
1794325029 43
1794325034 48
1794325039 48
1794325044 43
1794325049 43
1794325054 43
1794325059 43
1794325064 43
1794325069 43
1794325074 43
1794325079 43
```
</details>

---

