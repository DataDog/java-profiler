---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-18 05:19:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 54-76 cores)</summary>

```
1787044414 54
1787044419 54
1787044424 54
1787044429 54
1787044434 54
1787044439 54
1787044444 76
1787044449 76
1787044454 76
1787044459 76
1787044464 76
1787044469 76
1787044474 76
1787044479 76
1787044484 76
1787044489 76
1787044494 76
1787044499 76
1787044504 76
1787044509 76
```
</details>

---

