---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-29 12:33:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 12 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 77-79 cores)</summary>

```
1790699354 79
1790699359 79
1790699364 79
1790699369 79
1790699374 79
1790699379 79
1790699384 79
1790699389 79
1790699394 79
1790699399 79
1790699404 79
1790699409 79
1790699414 79
1790699419 77
1790699424 77
1790699429 77
1790699434 77
1790699439 77
1790699444 77
1790699449 77
```
</details>

---

