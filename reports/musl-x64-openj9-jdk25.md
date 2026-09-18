---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 09:29:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (4 unique values: 51-75 cores)</summary>

```
1789737759 75
1789737764 75
1789737769 75
1789737774 75
1789737779 67
1789737784 67
1789737789 67
1789737794 67
1789737799 67
1789737804 67
1789737809 67
1789737814 67
1789737819 67
1789737824 67
1789737829 68
1789737834 68
1789737839 51
1789737844 51
1789737849 51
1789737854 51
```
</details>

---

