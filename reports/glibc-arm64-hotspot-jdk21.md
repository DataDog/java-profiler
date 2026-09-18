---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 01:02:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 8 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789707398 48
1789707403 48
1789707408 48
1789707413 48
1789707418 48
1789707423 43
1789707428 43
1789707433 43
1789707438 43
1789707443 43
1789707448 43
1789707453 43
1789707458 43
1789707463 43
1789707468 43
1789707473 48
1789707478 48
1789707483 48
1789707488 48
1789707493 48
```
</details>

---

