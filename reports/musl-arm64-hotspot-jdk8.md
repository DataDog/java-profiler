---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-10 06:47:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 151 |
| Sample Rate | 2.52/sec |
| Health Score | 158% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 34 |
| Sample Rate | 0.57/sec |
| Health Score | 36% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1794310970 48
1794310975 48
1794310980 44
1794310985 44
1794310990 44
1794310995 44
1794311000 44
1794311005 44
1794311010 44
1794311015 44
1794311020 44
1794311025 44
1794311030 40
1794311035 40
1794311040 40
1794311045 40
1794311050 40
1794311055 40
1794311060 40
1794311065 40
```
</details>

---

