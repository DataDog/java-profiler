---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 05:17:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 41-43 cores)</summary>

```
1795083278 42
1795083283 42
1795083288 41
1795083293 41
1795083298 42
1795083303 42
1795083308 42
1795083313 42
1795083318 42
1795083323 42
1795083328 42
1795083333 42
1795083338 42
1795083343 43
1795083348 43
1795083353 43
1795083358 43
1795083363 43
1795083368 43
1795083373 42
```
</details>

---

