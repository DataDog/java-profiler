---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-14 08:32:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 7 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 43-51 cores)</summary>

```
1791980561 43
1791980566 43
1791980571 43
1791980576 43
1791980581 43
1791980586 43
1791980591 43
1791980596 43
1791980601 43
1791980606 43
1791980611 43
1791980617 43
1791980622 43
1791980627 43
1791980632 51
1791980637 51
1791980642 51
1791980647 51
1791980652 51
1791980657 51
```
</details>

---

