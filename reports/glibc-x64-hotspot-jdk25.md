---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 08:26:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (2 unique values: 78-80 cores)</summary>

```
1795785664 78
1795785669 78
1795785674 78
1795785679 78
1795785684 78
1795785689 78
1795785694 78
1795785699 80
1795785704 80
1795785709 80
1795785714 80
1795785719 80
1795785724 80
1795785729 80
1795785734 80
1795785739 80
1795785744 80
1795785749 78
1795785754 78
1795785759 78
```
</details>

---

