---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-29 00:58:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 8 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 62-66 cores)</summary>

```
1787979239 62
1787979244 62
1787979249 62
1787979254 62
1787979259 62
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
1787979334 66
```
</details>

---

