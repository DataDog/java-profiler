---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 09:06:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790168528 48
1790168533 48
1790168538 48
1790168543 48
1790168548 48
1790168553 48
1790168558 48
1790168563 48
1790168568 48
1790168573 48
1790168578 48
1790168583 48
1790168588 48
1790168593 48
1790168598 48
1790168603 48
1790168608 43
1790168613 43
1790168618 43
1790168623 43
```
</details>

---

