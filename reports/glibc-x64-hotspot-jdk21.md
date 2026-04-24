---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-24 12:55:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 9 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (3 unique values: 23-32 cores)</summary>

```
1777049458 32
1777049463 32
1777049468 32
1777049473 32
1777049478 32
1777049483 32
1777049488 32
1777049493 32
1777049498 32
1777049503 32
1777049508 32
1777049513 32
1777049518 32
1777049523 32
1777049528 32
1777049533 25
1777049538 25
1777049543 25
1777049548 25
1777049553 25
```
</details>

---

