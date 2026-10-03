---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-03 00:59:24 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 263 |
| Sample Rate | 4.38/sec |
| Health Score | 274% |
| Threads | 14 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1791003259 18
1791003264 18
1791003269 18
1791003274 18
1791003279 18
1791003284 18
1791003289 18
1791003294 18
1791003299 18
1791003304 18
1791003309 18
1791003314 13
1791003319 13
1791003324 13
1791003329 13
1791003334 13
1791003339 13
1791003344 13
1791003349 13
1791003354 13
```
</details>

---

