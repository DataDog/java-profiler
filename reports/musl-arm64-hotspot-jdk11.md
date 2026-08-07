---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 16:14:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 197 |
| Sample Rate | 3.28/sec |
| Health Score | 205% |
| Threads | 11 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 12 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (5 unique values: 16-27 cores)</summary>

```
1786133322 19
1786133327 19
1786133332 19
1786133337 19
1786133342 19
1786133347 19
1786133352 19
1786133357 19
1786133362 21
1786133367 21
1786133372 16
1786133377 16
1786133382 27
1786133387 27
1786133392 27
1786133397 27
1786133402 27
1786133407 27
1786133412 27
1786133417 27
```
</details>

---

