---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-17 14:55:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 40-58 cores)</summary>

```
1794945016 58
1794945021 58
1794945026 58
1794945031 58
1794945036 58
1794945041 58
1794945046 58
1794945051 58
1794945056 58
1794945061 45
1794945066 45
1794945071 40
1794945076 40
1794945081 40
1794945086 40
1794945091 40
1794945096 40
1794945101 40
1794945106 40
1794945111 45
```
</details>

---

