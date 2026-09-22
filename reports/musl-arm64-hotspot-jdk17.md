---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 16:59:29 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 10 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 39-49 cores)</summary>

```
1790110457 44
1790110462 44
1790110467 39
1790110472 39
1790110477 44
1790110482 44
1790110487 44
1790110492 44
1790110497 44
1790110502 44
1790110507 44
1790110512 44
1790110517 44
1790110522 49
1790110527 49
1790110532 49
1790110537 49
1790110542 44
1790110548 44
1790110553 44
```
</details>

---

