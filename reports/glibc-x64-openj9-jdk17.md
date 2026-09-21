---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 09:40:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 41-45 cores)</summary>

```
1789997749 43
1789997754 45
1789997759 45
1789997765 45
1789997770 45
1789997775 45
1789997780 45
1789997785 45
1789997790 45
1789997795 45
1789997800 45
1789997805 43
1789997810 43
1789997815 43
1789997820 43
1789997825 43
1789997830 43
1789997835 43
1789997840 43
1789997845 41
```
</details>

---

