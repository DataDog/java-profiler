---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 11:01:13 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 11 |
| Allocations | 116 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 11 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (3 unique values: 28-64 cores)</summary>

```
1794326259 56
1794326264 56
1794326269 56
1794326274 56
1794326279 56
1794326284 64
1794326289 64
1794326294 64
1794326299 64
1794326304 64
1794326309 64
1794326314 64
1794326319 64
1794326324 64
1794326329 64
1794326334 64
1794326339 64
1794326344 64
1794326349 64
1794326354 64
```
</details>

---

