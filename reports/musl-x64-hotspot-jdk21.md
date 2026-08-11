---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-11 14:11:49 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (4 unique values: 39-59 cores)</summary>

```
1786471586 42
1786471591 40
1786471596 40
1786471601 40
1786471606 40
1786471611 40
1786471616 40
1786471621 40
1786471626 40
1786471631 40
1786471636 40
1786471641 40
1786471646 40
1786471651 40
1786471656 40
1786471661 39
1786471666 39
1786471671 39
1786471676 39
1786471682 39
```
</details>

---

