---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ❌ FAIL

**Date:** 2026-09-22 09:50:45 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ⚠️
| Metric | Value |
|--------|-------|
| Status | N/A |
| CPU Samples | N/A |
| Sample Rate | N/A/sec |
| Health Score | N/A% |
| Threads | N/A |
| Allocations | N/A |

<details>
<summary>CPU Timeline (3 unique values: 89-92 cores)</summary>

```
1790084754 89
1790084759 89
1790084764 89
1790084769 92
1790084774 92
1790084779 92
1790084784 90
1790084789 90
1790084794 90
1790084799 90
1790084804 90
1790084809 90
1790084814 90
1790084819 90
1790084824 90
1790084829 90
```
</details>

---

