---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-22 16:32:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795382871 48
1795382876 48
1795382881 48
1795382886 48
1795382891 48
1795382896 48
1795382901 48
1795382906 48
1795382911 48
1795382916 48
1795382921 48
1795382926 48
1795382931 48
1795382936 43
1795382941 43
1795382946 43
1795382951 43
1795382956 43
1795382961 43
1795382966 43
```
</details>

---

