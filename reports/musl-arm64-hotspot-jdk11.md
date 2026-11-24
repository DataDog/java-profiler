---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 13:05:01 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 12 |
| Allocations | 110 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1130 |
| Sample Rate | 18.83/sec |
| Health Score | 1177% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 43-59 cores)</summary>

```
1795543251 43
1795543256 43
1795543261 43
1795543266 43
1795543271 43
1795543276 43
1795543281 43
1795543286 43
1795543291 43
1795543296 43
1795543301 43
1795543306 43
1795543311 43
1795543316 43
1795543321 43
1795543326 43
1795543331 43
1795543336 59
1795543342 59
1795543347 47
```
</details>

---

