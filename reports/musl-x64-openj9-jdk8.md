---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-18 05:19:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 78-96 cores)</summary>

```
1787044363 96
1787044368 96
1787044373 96
1787044378 96
1787044383 96
1787044388 96
1787044393 80
1787044398 80
1787044403 80
1787044408 80
1787044413 80
1787044418 78
1787044423 78
1787044428 78
1787044433 78
1787044438 78
1787044443 78
1787044448 78
1787044453 78
1787044458 78
```
</details>

---

