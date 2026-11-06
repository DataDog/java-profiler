---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-05 21:05:21 EST

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
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 255 |
| Sample Rate | 4.25/sec |
| Health Score | 266% |
| Threads | 14 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793930507 48
1793930512 48
1793930517 48
1793930522 48
1793930527 48
1793930532 48
1793930537 48
1793930542 48
1793930547 48
1793930552 48
1793930557 48
1793930562 48
1793930567 48
1793930572 48
1793930577 48
1793930582 48
1793930587 48
1793930592 48
1793930597 48
1793930602 48
```
</details>

---

