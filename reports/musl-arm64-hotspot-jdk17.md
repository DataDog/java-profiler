---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-27 16:16:20 EDT

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
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 9 |
| Allocations | 166 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 336 |
| Sample Rate | 5.60/sec |
| Health Score | 350% |
| Threads | 14 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787854932 48
1787854937 48
1787854942 48
1787854947 48
1787854952 48
1787854957 48
1787854962 43
1787854967 43
1787854972 43
1787854977 43
1787854982 43
1787854987 43
1787854992 43
1787854997 43
1787855002 43
1787855007 43
1787855012 43
1787855017 43
1787855022 48
1787855027 48
```
</details>

---

