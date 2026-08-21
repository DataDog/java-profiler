---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-21 03:04:22 EDT

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
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 8 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 38-48 cores)</summary>

```
1787295611 48
1787295616 48
1787295621 48
1787295626 48
1787295632 48
1787295637 48
1787295642 48
1787295647 48
1787295652 48
1787295657 48
1787295662 48
1787295667 48
1787295672 48
1787295677 48
1787295682 48
1787295687 48
1787295692 48
1787295697 48
1787295702 48
1787295707 48
```
</details>

---

