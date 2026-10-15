---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-15 09:57:53 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1792072340 32
1792072345 32
1792072350 32
1792072355 32
1792072360 32
1792072365 32
1792072370 32
1792072376 32
1792072381 32
1792072386 32
1792072391 32
1792072396 32
1792072401 32
1792072406 32
1792072411 32
1792072416 32
1792072421 32
1792072426 32
1792072431 32
1792072436 32
```
</details>

---

