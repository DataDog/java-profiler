---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-21 06:49:18 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 11 |
| Allocations | 402 |

<details>
<summary>CPU Timeline (3 unique values: 43-76 cores)</summary>

```
1792579489 63
1792579494 63
1792579499 63
1792579504 63
1792579509 63
1792579514 63
1792579519 63
1792579524 63
1792579529 63
1792579534 63
1792579539 63
1792579544 43
1792579549 43
1792579554 43
1792579559 43
1792579564 43
1792579569 43
1792579574 43
1792579579 43
1792579584 43
```
</details>

---

