---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 07:51:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 779 |
| Sample Rate | 12.98/sec |
| Health Score | 811% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (5 unique values: 35-72 cores)</summary>

```
1795524411 72
1795524416 72
1795524421 72
1795524426 44
1795524431 44
1795524436 44
1795524441 46
1795524446 46
1795524451 46
1795524456 46
1795524461 46
1795524466 46
1795524471 37
1795524476 37
1795524481 37
1795524486 37
1795524491 37
1795524496 37
1795524501 35
1795524506 35
```
</details>

---

