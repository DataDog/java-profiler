---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 08:37:36 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1795440788 44
1795440793 44
1795440798 44
1795440803 64
1795440808 64
1795440813 64
1795440818 64
1795440823 64
1795440828 64
1795440833 64
1795440838 64
1795440843 64
1795440848 64
1795440853 64
1795440858 64
1795440863 64
1795440868 64
1795440873 64
1795440878 64
1795440883 64
```
</details>

---

