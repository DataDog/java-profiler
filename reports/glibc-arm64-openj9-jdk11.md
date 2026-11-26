---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:25:28 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 6 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (3 unique values: 42-64 cores)</summary>

```
1795706343 42
1795706348 42
1795706353 42
1795706358 42
1795706363 42
1795706368 42
1795706373 42
1795706378 42
1795706383 42
1795706389 47
1795706394 47
1795706399 47
1795706404 47
1795706409 47
1795706414 47
1795706419 47
1795706424 47
1795706429 47
1795706434 47
1795706439 47
```
</details>

---

