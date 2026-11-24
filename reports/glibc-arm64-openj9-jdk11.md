---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 17:14:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 14 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795558197 33
1795558202 33
1795558207 33
1795558212 33
1795558217 33
1795558222 33
1795558227 33
1795558232 33
1795558237 33
1795558242 33
1795558247 33
1795558252 33
1795558257 28
1795558262 28
1795558267 28
1795558272 28
1795558277 28
1795558282 28
1795558287 28
1795558292 28
```
</details>

---

