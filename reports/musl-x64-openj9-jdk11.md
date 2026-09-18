---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:34:14 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 793 |
| Sample Rate | 13.22/sec |
| Health Score | 826% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1789719879 63
1789719884 63
1789719889 63
1789719894 63
1789719899 63
1789719904 63
1789719909 63
1789719914 63
1789719919 63
1789719924 61
1789719929 61
1789719934 61
1789719939 61
1789719944 61
1789719949 61
1789719954 61
1789719959 61
1789719964 61
1789719969 61
1789719974 63
```
</details>

---

