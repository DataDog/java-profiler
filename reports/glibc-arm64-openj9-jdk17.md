---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-07 10:19:22 EST

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
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 307 |
| Sample Rate | 5.12/sec |
| Health Score | 320% |
| Threads | 9 |
| Allocations | 155 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1794064512 24
1794064517 24
1794064522 24
1794064527 29
1794064532 29
1794064537 29
1794064542 29
1794064547 29
1794064552 29
1794064557 29
1794064562 29
1794064567 29
1794064572 29
1794064577 29
1794064582 29
1794064587 29
1794064592 29
1794064597 29
1794064602 29
1794064607 29
```
</details>

---

