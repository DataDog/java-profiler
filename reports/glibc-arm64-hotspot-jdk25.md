---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 12:27:58 EST

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
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795627473 64
1795627478 64
1795627483 64
1795627488 64
1795627493 64
1795627498 64
1795627503 64
1795627508 64
1795627513 64
1795627518 64
1795627523 64
1795627528 64
1795627533 64
1795627538 64
1795627543 64
1795627548 64
1795627553 64
1795627558 64
1795627563 64
1795627568 64
```
</details>

---

