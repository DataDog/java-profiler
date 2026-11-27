---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-27 08:24:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (3 unique values: 70-93 cores)</summary>

```
1795785561 91
1795785566 91
1795785571 91
1795785576 91
1795785581 91
1795785586 91
1795785591 91
1795785596 91
1795785601 91
1795785606 91
1795785611 91
1795785616 91
1795785621 91
1795785626 93
1795785631 93
1795785636 93
1795785641 93
1795785646 93
1795785651 93
1795785656 93
```
</details>

---

