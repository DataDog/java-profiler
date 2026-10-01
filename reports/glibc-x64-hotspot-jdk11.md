---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-01 07:23:41 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 830 |
| Sample Rate | 13.83/sec |
| Health Score | 864% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 71-81 cores)</summary>

```
1790853541 81
1790853546 81
1790853551 81
1790853556 81
1790853561 81
1790853566 81
1790853571 81
1790853576 81
1790853581 81
1790853586 81
1790853591 81
1790853596 81
1790853601 81
1790853606 81
1790853611 81
1790853616 81
1790853621 81
1790853626 81
1790853631 73
1790853636 73
```
</details>

---

