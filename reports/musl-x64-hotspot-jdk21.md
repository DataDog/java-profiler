---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 12:33:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 806 |
| Sample Rate | 13.43/sec |
| Health Score | 839% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (4 unique values: 65-72 cores)</summary>

```
1795022910 65
1795022915 65
1795022920 65
1795022925 65
1795022930 65
1795022935 67
1795022940 67
1795022945 67
1795022950 67
1795022955 67
1795022960 67
1795022965 69
1795022970 69
1795022975 69
1795022980 69
1795022985 69
1795022990 69
1795022995 69
1795023000 72
1795023005 72
```
</details>

---

