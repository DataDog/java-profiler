---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:28:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 8 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 70-96 cores)</summary>

```
1795641764 70
1795641769 70
1795641774 70
1795641779 96
1795641784 96
1795641789 96
1795641794 96
1795641799 96
1795641804 96
1795641809 96
1795641814 96
1795641819 96
1795641824 96
1795641829 70
1795641834 70
1795641839 70
1795641844 70
1795641849 70
1795641854 70
1795641859 70
```
</details>

---

