---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-25 10:02:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 84-87 cores)</summary>

```
1795618609 84
1795618614 84
1795618619 84
1795618624 84
1795618629 84
1795618634 87
1795618639 87
1795618644 87
1795618649 87
1795618654 87
1795618659 87
1795618664 87
1795618669 87
1795618674 87
1795618679 87
1795618684 87
1795618689 87
1795618694 85
1795618699 85
1795618704 85
```
</details>

---

