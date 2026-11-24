---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 13:04:59 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 9 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1795543266 48
1795543271 48
1795543276 48
1795543281 48
1795543286 48
1795543291 48
1795543296 48
1795543301 48
1795543306 48
1795543311 48
1795543316 48
1795543321 48
1795543326 48
1795543331 48
1795543336 48
1795543341 48
1795543346 48
1795543351 43
1795543356 43
1795543361 43
```
</details>

---

