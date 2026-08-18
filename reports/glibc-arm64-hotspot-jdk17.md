---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-18 05:19:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 15 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787044430 48
1787044435 48
1787044440 48
1787044445 48
1787044451 48
1787044456 43
1787044461 43
1787044466 43
1787044471 43
1787044476 43
1787044481 43
1787044486 43
1787044491 43
1787044496 43
1787044501 43
1787044506 43
1787044511 43
1787044516 43
1787044521 43
1787044526 48
```
</details>

---

