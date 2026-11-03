---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 21:59:30 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 14 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1793674477 48
1793674482 48
1793674487 48
1793674492 48
1793674497 48
1793674502 48
1793674507 48
1793674512 48
1793674517 48
1793674522 48
1793674527 48
1793674532 48
1793674537 48
1793674542 48
1793674547 48
1793674552 48
1793674557 36
1793674562 36
1793674567 36
1793674572 36
```
</details>

---

