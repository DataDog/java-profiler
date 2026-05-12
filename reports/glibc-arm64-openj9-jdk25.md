---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-12 06:46:27 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 12 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778582414 64
1778582419 64
1778582424 64
1778582429 64
1778582434 64
1778582439 64
1778582444 64
1778582449 64
1778582454 64
1778582459 64
1778582464 64
1778582469 64
1778582474 64
1778582479 64
1778582484 64
1778582489 64
1778582494 64
1778582499 64
1778582504 64
1778582509 64
```
</details>

---

