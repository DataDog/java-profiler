---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-15 05:55:38 EDT

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (3 unique values: 10-32 cores)</summary>

```
1792057824 10
1792057829 30
1792057834 30
1792057839 30
1792057844 30
1792057849 30
1792057854 32
1792057859 32
1792057864 32
1792057869 32
1792057874 32
1792057879 32
1792057884 32
1792057889 32
1792057894 32
1792057899 32
1792057904 32
1792057909 32
1792057914 32
1792057919 32
```
</details>

---

