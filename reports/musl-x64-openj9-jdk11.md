---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-25 21:27:19 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 834 |
| Sample Rate | 13.90/sec |
| Health Score | 869% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (5 unique values: 44-81 cores)</summary>

```
1792977804 46
1792977809 46
1792977814 46
1792977819 46
1792977824 46
1792977829 46
1792977834 44
1792977840 44
1792977845 44
1792977850 44
1792977855 44
1792977860 44
1792977865 61
1792977870 61
1792977875 46
1792977880 46
1792977885 46
1792977890 48
1792977895 48
1792977900 48
```
</details>

---

