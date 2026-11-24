---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 11:39:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 39-55 cores)</summary>

```
1795537847 39
1795537852 39
1795537857 39
1795537862 39
1795537867 39
1795537872 39
1795537877 39
1795537882 39
1795537887 39
1795537892 39
1795537897 39
1795537902 39
1795537907 39
1795537912 39
1795537917 39
1795537922 39
1795537927 55
1795537933 55
1795537938 55
1795537943 55
```
</details>

---

