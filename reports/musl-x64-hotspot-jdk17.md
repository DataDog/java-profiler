---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 08:24:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 37 |
| Sample Rate | 0.62/sec |
| Health Score | 39% |
| Threads | 9 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 34-52 cores)</summary>

```
1795785598 34
1795785603 34
1795785608 34
1795785613 34
1795785618 34
1795785623 43
1795785628 43
1795785633 43
1795785638 43
1795785643 43
1795785648 43
1795785653 43
1795785659 43
1795785664 52
1795785669 52
1795785674 52
1795785679 52
1795785684 52
1795785689 52
1795785694 52
```
</details>

---

