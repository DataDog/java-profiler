---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 06:36:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 813 |
| Sample Rate | 13.55/sec |
| Health Score | 847% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 42-63 cores)</summary>

```
1794396689 58
1794396694 58
1794396699 58
1794396704 58
1794396709 58
1794396714 58
1794396719 58
1794396724 58
1794396729 58
1794396734 58
1794396739 60
1794396744 60
1794396749 60
1794396754 60
1794396759 60
1794396764 60
1794396769 60
1794396774 60
1794396779 60
1794396784 60
```
</details>

---

