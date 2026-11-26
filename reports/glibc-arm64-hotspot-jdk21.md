---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 08:21:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795699046 64
1795699051 64
1795699056 64
1795699061 64
1795699066 64
1795699071 64
1795699076 64
1795699081 64
1795699086 64
1795699091 64
1795699096 64
1795699101 64
1795699106 64
1795699111 64
1795699116 64
1795699121 64
1795699126 64
1795699131 64
1795699136 64
1795699141 64
```
</details>

---

