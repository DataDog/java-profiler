---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-05 05:52:35 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (3 unique values: 57-86 cores)</summary>

```
1791193586 86
1791193591 86
1791193596 86
1791193601 86
1791193606 86
1791193611 86
1791193616 86
1791193621 86
1791193626 86
1791193631 86
1791193636 86
1791193641 86
1791193646 86
1791193651 57
1791193656 57
1791193661 57
1791193666 57
1791193671 57
1791193676 57
1791193681 57
```
</details>

---

