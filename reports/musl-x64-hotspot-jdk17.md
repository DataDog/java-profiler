---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 06:10:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (4 unique values: 62-72 cores)</summary>

```
1786356259 72
1786356264 70
1786356269 70
1786356274 70
1786356279 62
1786356284 62
1786356289 62
1786356294 62
1786356299 62
1786356304 62
1786356309 64
1786356314 64
1786356319 62
1786356324 62
1786356329 62
1786356334 62
1786356339 62
1786356344 62
1786356349 62
1786356354 62
```
</details>

---

