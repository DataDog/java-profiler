---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-30 07:31:56 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 29-76 cores)</summary>

```
1790767607 76
1790767612 76
1790767617 76
1790767622 76
1790767627 76
1790767632 76
1790767637 76
1790767642 76
1790767647 76
1790767652 76
1790767657 76
1790767662 76
1790767667 76
1790767672 76
1790767677 76
1790767682 76
1790767687 76
1790767692 29
1790767697 29
1790767702 29
```
</details>

---

