---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-23 21:22:04 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1787534318 46
1787534323 46
1787534328 46
1787534333 46
1787534338 46
1787534343 46
1787534348 46
1787534353 46
1787534358 46
1787534363 46
1787534368 43
1787534373 43
1787534378 43
1787534383 43
1787534388 43
1787534393 43
1787534398 43
1787534403 43
1787534408 43
1787534413 43
```
</details>

---

