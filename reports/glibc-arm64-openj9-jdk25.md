---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 05:55:18 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 40 |
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
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (5 unique values: 40-48 cores)</summary>

```
1794394291 45
1794394296 45
1794394301 40
1794394306 40
1794394311 42
1794394316 42
1794394321 43
1794394326 43
1794394331 43
1794394336 43
1794394341 43
1794394346 43
1794394351 43
1794394356 43
1794394361 48
1794394366 48
1794394371 48
1794394376 48
1794394381 48
1794394386 48
```
</details>

---

