---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 14:55:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794945036 46
1794945041 46
1794945046 46
1794945051 46
1794945056 46
1794945061 46
1794945066 46
1794945071 46
1794945076 46
1794945081 46
1794945086 46
1794945091 46
1794945096 51
1794945101 51
1794945106 51
1794945111 51
1794945116 51
1794945121 51
1794945126 51
1794945131 51
```
</details>

---

