---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 12:29:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
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
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 9 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1795627448 44
1795627453 44
1795627458 44
1795627463 44
1795627468 44
1795627473 44
1795627478 44
1795627483 44
1795627488 44
1795627493 44
1795627498 44
1795627503 44
1795627508 64
1795627513 64
1795627518 64
1795627523 64
1795627528 64
1795627533 64
1795627538 64
1795627543 64
```
</details>

---

