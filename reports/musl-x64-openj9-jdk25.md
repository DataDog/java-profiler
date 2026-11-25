---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 16:28:14 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 39 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 66-68 cores)</summary>

```
1795641758 68
1795641763 68
1795641768 68
1795641773 68
1795641779 68
1795641784 68
1795641789 68
1795641794 68
1795641799 68
1795641804 66
1795641809 66
1795641814 66
1795641819 66
1795641824 66
1795641829 66
1795641834 66
1795641839 66
1795641844 66
1795641849 66
1795641854 66
```
</details>

---

