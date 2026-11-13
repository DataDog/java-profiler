---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 03:42:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 8 |
| Allocations | 91 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 11 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794559021 32
1794559026 32
1794559031 32
1794559036 32
1794559041 32
1794559046 32
1794559051 32
1794559056 32
1794559061 32
1794559066 32
1794559071 32
1794559076 32
1794559081 32
1794559086 32
1794559091 32
1794559096 32
1794559101 32
1794559106 32
1794559111 32
1794559116 32
```
</details>

---

