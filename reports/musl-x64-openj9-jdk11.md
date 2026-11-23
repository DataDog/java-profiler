---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 00:00:38 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 9 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 29-51 cores)</summary>

```
1795409764 29
1795409769 31
1795409774 31
1795409779 31
1795409784 31
1795409789 31
1795409794 31
1795409799 31
1795409804 31
1795409809 31
1795409814 31
1795409819 51
1795409824 51
1795409829 51
1795409834 51
1795409839 51
1795409844 51
1795409849 51
1795409854 51
1795409859 51
```
</details>

---

