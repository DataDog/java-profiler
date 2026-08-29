---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-29 00:58:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787979254 64
1787979259 64
1787979264 64
1787979269 64
1787979274 64
1787979279 64
1787979284 64
1787979289 64
1787979294 64
1787979299 64
1787979304 64
1787979309 64
1787979314 64
1787979319 64
1787979324 64
1787979329 64
1787979334 64
1787979339 64
1787979344 64
1787979349 64
```
</details>

---

