---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 11:39:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 9 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (5 unique values: 64-79 cores)</summary>

```
1795537827 64
1795537832 64
1795537837 75
1795537842 75
1795537847 75
1795537852 75
1795537857 75
1795537862 77
1795537867 77
1795537872 79
1795537877 79
1795537882 79
1795537887 79
1795537892 79
1795537897 79
1795537902 79
1795537907 79
1795537912 79
1795537917 79
1795537922 79
```
</details>

---

