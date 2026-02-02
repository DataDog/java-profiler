---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-02-02 12:03:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1770051400 24
1770051405 24
1770051410 24
1770051415 24
1770051420 24
1770051425 24
1770051430 24
1770051435 24
1770051440 24
1770051445 24
1770051450 24
1770051455 24
1770051460 24
1770051465 24
1770051470 24
1770051475 24
1770051480 24
1770051485 24
1770051490 24
1770051495 24
```
</details>

---

