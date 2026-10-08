---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-08 10:10:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (4 unique values: 39-48 cores)</summary>

```
1791468254 48
1791468259 48
1791468264 48
1791468269 48
1791468274 43
1791468279 43
1791468284 43
1791468289 40
1791468294 40
1791468299 40
1791468304 40
1791468309 40
1791468314 40
1791468319 40
1791468324 40
1791468329 40
1791468334 40
1791468339 40
1791468344 40
1791468349 39
```
</details>

---

