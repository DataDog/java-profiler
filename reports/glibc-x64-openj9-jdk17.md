---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 12:53:34 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 905 |
| Sample Rate | 15.08/sec |
| Health Score | 942% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (6 unique values: 47-88 cores)</summary>

```
1778172532 86
1778172537 86
1778172542 86
1778172547 86
1778172552 88
1778172557 88
1778172562 88
1778172567 88
1778172572 83
1778172577 83
1778172582 83
1778172587 83
1778172592 83
1778172597 83
1778172602 83
1778172607 83
1778172612 83
1778172617 83
1778172622 79
1778172627 79
```
</details>

---

