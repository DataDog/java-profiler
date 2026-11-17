---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 12:45:53 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 139 |
| Sample Rate | 2.32/sec |
| Health Score | 145% |
| Threads | 10 |
| Allocations | 101 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 13 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 26-31 cores)</summary>

```
1794937288 26
1794937293 26
1794937298 26
1794937303 26
1794937308 26
1794937313 26
1794937318 26
1794937323 26
1794937328 26
1794937333 26
1794937338 26
1794937343 26
1794937348 26
1794937353 26
1794937358 26
1794937363 31
1794937368 31
1794937373 31
1794937378 31
1794937383 31
```
</details>

---

