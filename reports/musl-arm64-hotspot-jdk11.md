---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-01 01:04:52 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 139 |
| Sample Rate | 2.32/sec |
| Health Score | 145% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 13 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1793509244 34
1793509249 34
1793509254 29
1793509259 29
1793509264 29
1793509269 29
1793509274 29
1793509279 29
1793509284 29
1793509289 29
1793509294 29
1793509299 29
1793509304 29
1793509309 29
1793509314 29
1793509319 29
1793509324 29
1793509329 29
1793509334 29
1793509339 29
```
</details>

---

