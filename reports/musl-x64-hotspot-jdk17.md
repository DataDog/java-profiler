---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-05 15:44:31 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 9 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (4 unique values: 47-64 cores)</summary>

```
1772743304 64
1772743309 64
1772743314 64
1772743319 64
1772743324 64
1772743329 64
1772743334 64
1772743339 64
1772743344 59
1772743349 59
1772743354 59
1772743359 59
1772743364 59
1772743369 59
1772743374 59
1772743379 59
1772743384 59
1772743389 47
1772743394 47
1772743399 47
```
</details>

---

