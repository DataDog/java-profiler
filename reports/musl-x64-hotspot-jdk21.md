---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 09:37:46 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 9 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 812 |
| Sample Rate | 13.53/sec |
| Health Score | 846% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 54-56 cores)</summary>

```
1794839611 56
1794839616 56
1794839621 56
1794839626 56
1794839631 56
1794839636 56
1794839641 54
1794839646 54
1794839651 54
1794839656 54
1794839661 54
1794839666 54
1794839671 54
1794839676 54
1794839681 54
1794839686 54
1794839691 54
1794839696 54
1794839701 54
1794839706 54
```
</details>

---

