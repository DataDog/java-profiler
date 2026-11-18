---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:06:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 82-87 cores)</summary>

```
1795010503 87
1795010508 87
1795010513 82
1795010518 82
1795010523 82
1795010528 82
1795010533 82
1795010538 82
1795010543 82
1795010548 82
1795010553 82
1795010558 82
1795010563 82
1795010568 82
1795010573 82
1795010578 82
1795010583 82
1795010588 82
1795010593 82
1795010598 82
```
</details>

---

