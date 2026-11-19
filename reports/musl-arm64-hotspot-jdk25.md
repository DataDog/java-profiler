---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 06:06:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 13 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (5 unique values: 38-51 cores)</summary>

```
1795085932 51
1795085937 49
1795085942 49
1795085947 49
1795085952 49
1795085957 49
1795085962 49
1795085967 44
1795085972 44
1795085977 44
1795085982 44
1795085987 44
1795085992 44
1795085997 44
1795086002 44
1795086007 44
1795086012 44
1795086017 44
1795086022 44
1795086027 44
```
</details>

---

