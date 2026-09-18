---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 02:31:40 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 8 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1789712744 17
1789712749 17
1789712754 17
1789712759 17
1789712764 17
1789712769 17
1789712774 17
1789712779 17
1789712784 15
1789712789 15
1789712794 15
1789712799 15
1789712804 15
1789712809 15
1789712814 15
1789712819 15
1789712824 15
1789712829 15
1789712834 15
1789712840 15
```
</details>

---

