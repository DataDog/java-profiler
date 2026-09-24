---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 04:39:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 379 |
| Sample Rate | 6.32/sec |
| Health Score | 395% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (4 unique values: 40-45 cores)</summary>

```
1790238932 40
1790238937 40
1790238942 40
1790238947 40
1790238952 42
1790238957 42
1790238962 42
1790238967 42
1790238972 42
1790238977 42
1790238982 42
1790238987 42
1790238992 42
1790238997 42
1790239002 42
1790239007 42
1790239012 44
1790239017 44
1790239022 44
1790239027 44
```
</details>

---

