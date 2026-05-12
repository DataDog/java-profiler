---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-12 03:57:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1038 |
| Sample Rate | 17.30/sec |
| Health Score | 1081% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1778572276 44
1778572281 49
1778572286 49
1778572291 49
1778572296 49
1778572301 49
1778572306 49
1778572311 49
1778572316 49
1778572321 49
1778572326 49
1778572331 49
1778572336 49
1778572341 49
1778572346 49
1778572351 49
1778572356 49
1778572361 49
1778572366 49
1778572371 49
```
</details>

---

