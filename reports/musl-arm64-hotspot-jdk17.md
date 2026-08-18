---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-17 21:38:42 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 8 |
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 334 |
| Sample Rate | 5.57/sec |
| Health Score | 348% |
| Threads | 13 |
| Allocations | 101 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787016833 48
1787016838 48
1787016843 48
1787016848 48
1787016853 43
1787016858 43
1787016863 43
1787016868 43
1787016873 43
1787016878 43
1787016883 43
1787016888 43
1787016893 43
1787016898 43
1787016903 48
1787016908 48
1787016913 48
1787016918 48
1787016923 48
1787016928 48
```
</details>

---

