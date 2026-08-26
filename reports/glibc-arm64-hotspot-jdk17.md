---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-26 10:30:25 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 7 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 162 |
| Sample Rate | 2.70/sec |
| Health Score | 169% |
| Threads | 13 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1787754417 40
1787754422 40
1787754427 40
1787754432 40
1787754437 40
1787754442 40
1787754447 40
1787754452 40
1787754457 40
1787754462 40
1787754467 40
1787754472 40
1787754477 40
1787754482 40
1787754487 40
1787754492 40
1787754497 40
1787754502 40
1787754507 40
1787754512 40
```
</details>

---

