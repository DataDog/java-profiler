---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:02:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 80-85 cores)</summary>

```
1795618629 82
1795618634 82
1795618639 82
1795618644 82
1795618649 82
1795618654 82
1795618659 82
1795618664 82
1795618669 82
1795618674 82
1795618679 82
1795618684 82
1795618689 82
1795618694 82
1795618699 82
1795618704 82
1795618709 80
1795618714 80
1795618719 80
1795618724 85
```
</details>

---

