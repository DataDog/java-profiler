---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 11:42:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 9 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 11 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1795538332 44
1795538337 44
1795538342 44
1795538347 44
1795538352 44
1795538357 44
1795538362 44
1795538367 44
1795538372 44
1795538377 44
1795538382 44
1795538387 44
1795538392 44
1795538397 44
1795538402 44
1795538407 44
1795538412 44
1795538417 64
1795538422 64
1795538427 64
```
</details>

---

