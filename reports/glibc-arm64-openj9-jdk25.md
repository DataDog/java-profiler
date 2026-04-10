---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-10 09:15:12 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 13 |
| Allocations | 159 |

<details>
<summary>CPU Timeline (3 unique values: 59-64 cores)</summary>

```
1775826559 59
1775826564 59
1775826569 59
1775826574 59
1775826579 59
1775826584 59
1775826589 64
1775826594 64
1775826599 64
1775826604 64
1775826609 64
1775826614 64
1775826619 64
1775826624 64
1775826629 64
1775826634 64
1775826639 64
1775826644 64
1775826649 59
1775826654 59
```
</details>

---

