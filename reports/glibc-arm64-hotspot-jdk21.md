---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 12:27:58 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 8 |
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 422 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1795627457 44
1795627462 44
1795627467 44
1795627472 44
1795627477 44
1795627483 44
1795627488 44
1795627493 44
1795627498 44
1795627503 44
1795627508 44
1795627513 44
1795627518 44
1795627523 44
1795627528 44
1795627533 44
1795627538 44
1795627543 44
1795627548 44
1795627553 44
```
</details>

---

