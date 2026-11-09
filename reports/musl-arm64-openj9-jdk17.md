---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-09 18:48:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 317 |
| Sample Rate | 5.28/sec |
| Health Score | 330% |
| Threads | 10 |
| Allocations | 135 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 13 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (3 unique values: 39-64 cores)</summary>

```
1794267903 39
1794267908 39
1794267913 39
1794267918 39
1794267923 39
1794267928 39
1794267933 39
1794267938 39
1794267943 39
1794267948 39
1794267953 64
1794267958 64
1794267963 64
1794267968 64
1794267973 64
1794267978 64
1794267983 64
1794267988 64
1794267993 64
1794267998 64
```
</details>

---

