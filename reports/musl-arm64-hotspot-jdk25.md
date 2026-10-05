---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-05 05:52:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (3 unique values: 37-51 cores)</summary>

```
1791193596 37
1791193601 37
1791193606 39
1791193611 39
1791193616 39
1791193621 39
1791193626 39
1791193631 39
1791193636 39
1791193641 39
1791193646 39
1791193651 39
1791193656 51
1791193661 51
1791193666 51
1791193671 51
1791193676 51
1791193681 51
1791193686 51
1791193691 51
```
</details>

---

