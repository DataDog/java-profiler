---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 06:07:17 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (4 unique values: 49-81 cores)</summary>

```
1790675859 49
1790675864 49
1790675869 49
1790675874 49
1790675879 49
1790675884 51
1790675889 51
1790675894 49
1790675899 49
1790675904 49
1790675909 79
1790675914 79
1790675919 81
1790675924 81
1790675929 81
1790675934 81
1790675939 81
1790675944 81
1790675949 81
1790675954 81
```
</details>

---

