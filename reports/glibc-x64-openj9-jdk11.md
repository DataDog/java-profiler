---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 08:37:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 87-96 cores)</summary>

```
1795440769 96
1795440774 96
1795440779 96
1795440784 87
1795440789 87
1795440794 87
1795440799 87
1795440804 87
1795440809 87
1795440814 87
1795440819 87
1795440824 87
1795440829 87
1795440834 87
1795440839 87
1795440844 87
1795440849 87
1795440854 87
1795440859 87
1795440864 87
```
</details>

---

