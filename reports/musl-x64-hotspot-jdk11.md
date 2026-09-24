---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 04:39:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 833 |
| Sample Rate | 13.88/sec |
| Health Score | 868% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (5 unique values: 86-94 cores)</summary>

```
1790238927 94
1790238932 94
1790238937 94
1790238942 94
1790238947 94
1790238952 94
1790238957 94
1790238962 94
1790238967 94
1790238972 90
1790238977 90
1790238982 90
1790238987 90
1790238992 90
1790238997 90
1790239002 89
1790239007 89
1790239012 89
1790239017 93
1790239022 93
```
</details>

---

