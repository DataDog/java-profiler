---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 02:29:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 977 |
| Sample Rate | 16.28/sec |
| Health Score | 1018% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 90-96 cores)</summary>

```
1789712734 90
1789712739 90
1789712744 92
1789712749 92
1789712754 92
1789712759 92
1789712764 92
1789712769 92
1789712774 92
1789712779 92
1789712784 92
1789712789 92
1789712794 92
1789712799 92
1789712804 92
1789712809 92
1789712814 92
1789712819 92
1789712824 96
1789712829 96
```
</details>

---

