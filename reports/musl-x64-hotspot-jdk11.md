---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 02:29:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 8 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 954 |
| Sample Rate | 15.90/sec |
| Health Score | 994% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 57-61 cores)</summary>

```
1789712734 57
1789712739 57
1789712744 57
1789712749 57
1789712754 57
1789712759 57
1789712764 57
1789712769 57
1789712774 57
1789712779 57
1789712784 57
1789712789 57
1789712794 57
1789712799 57
1789712804 57
1789712809 59
1789712814 59
1789712819 59
1789712824 59
1789712829 59
```
</details>

---

