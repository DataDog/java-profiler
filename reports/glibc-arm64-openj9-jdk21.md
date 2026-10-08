---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-08 10:10:19 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 15 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1791468301 43
1791468306 43
1791468311 43
1791468316 43
1791468321 43
1791468326 43
1791468331 43
1791468336 43
1791468341 43
1791468346 43
1791468351 43
1791468356 43
1791468361 43
1791468366 43
1791468371 38
1791468376 38
1791468381 38
1791468386 38
1791468391 38
1791468396 38
```
</details>

---

