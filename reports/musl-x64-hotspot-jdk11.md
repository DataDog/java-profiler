---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-05 05:52:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 12-32 cores)</summary>

```
1791193586 12
1791193591 12
1791193596 12
1791193601 12
1791193606 12
1791193611 12
1791193616 12
1791193621 12
1791193626 12
1791193631 12
1791193636 12
1791193641 12
1791193646 12
1791193651 12
1791193656 32
1791193661 32
1791193666 32
1791193671 32
1791193676 32
1791193681 32
```
</details>

---

