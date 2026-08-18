---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-18 05:19:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 332 |
| Sample Rate | 5.53/sec |
| Health Score | 346% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 80-96 cores)</summary>

```
1787044387 96
1787044392 96
1787044397 96
1787044402 96
1787044407 96
1787044412 96
1787044417 96
1787044422 96
1787044427 96
1787044432 96
1787044437 96
1787044442 88
1787044447 88
1787044452 88
1787044457 88
1787044462 88
1787044467 88
1787044472 88
1787044477 88
1787044482 88
```
</details>

---

