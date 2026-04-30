---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-30 19:50:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 58-83 cores)</summary>

```
1777592834 61
1777592839 58
1777592844 58
1777592849 63
1777592854 63
1777592859 63
1777592864 63
1777592869 63
1777592874 73
1777592879 73
1777592884 73
1777592889 73
1777592894 73
1777592899 78
1777592904 78
1777592909 83
1777592914 83
1777592919 83
1777592924 83
1777592929 83
```
</details>

---

