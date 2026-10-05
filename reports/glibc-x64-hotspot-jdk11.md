---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-05 05:52:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 42-62 cores)</summary>

```
1791193596 42
1791193601 42
1791193606 42
1791193611 42
1791193616 42
1791193621 42
1791193626 42
1791193631 42
1791193636 42
1791193641 42
1791193646 42
1791193651 42
1791193656 42
1791193661 42
1791193666 42
1791193671 42
1791193676 42
1791193681 42
1791193686 42
1791193691 62
```
</details>

---

