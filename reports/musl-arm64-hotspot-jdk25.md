---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 11:01:36 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (3 unique values: 33-48 cores)</summary>

```
1793112870 48
1793112875 48
1793112880 48
1793112885 48
1793112890 37
1793112895 37
1793112900 37
1793112905 37
1793112910 37
1793112915 37
1793112920 33
1793112925 33
1793112930 33
1793112935 33
1793112940 33
1793112945 33
1793112950 33
1793112955 33
1793112960 33
1793112965 33
```
</details>

---

