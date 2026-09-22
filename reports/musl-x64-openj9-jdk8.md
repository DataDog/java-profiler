---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-22 12:32:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 322 |
| Sample Rate | 5.37/sec |
| Health Score | 336% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 55-86 cores)</summary>

```
1790093842 63
1790093847 63
1790093852 65
1790093857 65
1790093862 65
1790093867 65
1790093872 65
1790093877 65
1790093882 65
1790093887 65
1790093892 65
1790093897 65
1790093902 65
1790093907 65
1790093912 65
1790093917 65
1790093922 86
1790093927 86
1790093932 55
1790093937 55
```
</details>

---

