---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-15 05:55:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 951 |
| Sample Rate | 15.85/sec |
| Health Score | 991% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 59-63 cores)</summary>

```
1792057829 59
1792057834 59
1792057839 59
1792057844 59
1792057849 59
1792057854 59
1792057859 59
1792057864 59
1792057869 59
1792057874 59
1792057879 59
1792057884 63
1792057889 63
1792057894 63
1792057899 63
1792057904 63
1792057909 63
1792057914 63
1792057919 63
1792057924 63
```
</details>

---

