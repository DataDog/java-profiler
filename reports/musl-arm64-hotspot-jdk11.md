---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:34:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 27-44 cores)</summary>

```
1789719884 27
1789719889 27
1789719894 44
1789719899 44
1789719904 44
1789719909 44
1789719914 44
1789719919 44
1789719924 44
1789719929 44
1789719934 44
1789719939 44
1789719944 44
1789719949 44
1789719954 44
1789719959 44
1789719964 44
1789719969 44
1789719974 44
1789719980 44
```
</details>

---

