---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 02:29:46 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1789712724 79
1789712729 79
1789712734 79
1789712739 79
1789712744 79
1789712749 79
1789712754 79
1789712759 79
1789712764 79
1789712769 79
1789712774 81
1789712779 81
1789712784 81
1789712789 81
1789712794 81
1789712799 81
1789712804 81
1789712809 81
1789712814 81
1789712819 81
```
</details>

---

