---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 06:38:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 10 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 15-15 cores)</summary>

```
1795001614 15
1795001619 15
1795001624 15
1795001629 15
1795001634 15
1795001639 15
1795001644 15
1795001649 15
1795001654 15
1795001659 15
1795001664 15
1795001669 15
1795001674 15
1795001679 15
1795001684 15
1795001689 15
1795001694 15
1795001699 15
1795001704 15
1795001709 15
```
</details>

---

