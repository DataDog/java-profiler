---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 11:31:14 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 69-72 cores)</summary>

```
1795105551 70
1795105556 70
1795105561 70
1795105566 70
1795105571 70
1795105576 70
1795105581 70
1795105586 70
1795105591 70
1795105596 70
1795105601 70
1795105606 70
1795105611 72
1795105616 72
1795105621 72
1795105626 69
1795105631 69
1795105636 69
1795105641 69
1795105646 69
```
</details>

---

