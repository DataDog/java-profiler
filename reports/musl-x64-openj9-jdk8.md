---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-30 11:47:35 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 335 |
| Sample Rate | 5.58/sec |
| Health Score | 349% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1793374854 60
1793374859 60
1793374864 60
1793374869 60
1793374874 60
1793374879 60
1793374884 60
1793374889 60
1793374894 60
1793374899 60
1793374904 60
1793374909 60
1793374914 60
1793374919 60
1793374924 60
1793374929 60
1793374934 60
1793374939 60
1793374944 62
1793374949 62
```
</details>

---

