---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 13:04:59 EST

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
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795543260 64
1795543265 64
1795543270 64
1795543276 64
1795543281 64
1795543286 64
1795543291 64
1795543296 64
1795543301 64
1795543306 64
1795543311 64
1795543316 64
1795543321 64
1795543326 64
1795543331 64
1795543336 64
1795543341 64
1795543346 64
1795543351 64
1795543356 64
```
</details>

---

