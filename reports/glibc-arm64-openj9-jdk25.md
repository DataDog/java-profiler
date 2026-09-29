---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-29 02:36:38 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790663533 43
1790663538 43
1790663543 43
1790663548 43
1790663553 43
1790663558 43
1790663563 43
1790663568 43
1790663573 43
1790663578 43
1790663583 43
1790663588 43
1790663593 43
1790663598 43
1790663603 43
1790663608 43
1790663613 43
1790663618 43
1790663623 43
1790663628 43
```
</details>

---

