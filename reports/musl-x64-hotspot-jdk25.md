---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-29 06:14:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 19.40/sec |
| Health Score | 1212% |
| Threads | 10 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 841 |
| Sample Rate | 28.03/sec |
| Health Score | 1752% |
| Threads | 12 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1769684967 29
1769684972 29
1769684977 29
1769684982 29
1769684987 29
1769684992 29
1769684997 29
1769685002 29
1769685007 29
1769685012 29
1769685017 29
1769685022 32
1769685027 32
1769685032 32
1769685037 32
1769685042 32
1769685047 32
1769685052 32
1769685057 32
1769685062 32
```
</details>

---

