---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-18 05:19:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 78-96 cores)</summary>

```
1787044359 96
1787044364 96
1787044369 96
1787044374 96
1787044379 96
1787044384 96
1787044389 96
1787044394 80
1787044399 80
1787044404 80
1787044409 80
1787044414 80
1787044419 78
1787044424 78
1787044429 78
1787044434 78
1787044439 78
1787044444 78
1787044449 78
1787044454 78
```
</details>

---

