---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-06 10:08:45 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 244 |
| Sample Rate | 4.07/sec |
| Health Score | 254% |
| Threads | 11 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1791295502 40
1791295507 40
1791295512 40
1791295517 40
1791295522 40
1791295527 35
1791295532 35
1791295537 35
1791295542 35
1791295547 35
1791295552 35
1791295557 35
1791295562 35
1791295567 35
1791295572 35
1791295577 35
1791295582 35
1791295587 35
1791295592 35
1791295597 35
```
</details>

---

