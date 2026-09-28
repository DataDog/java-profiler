---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 10:16:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 833 |
| Sample Rate | 13.88/sec |
| Health Score | 868% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1790604692 81
1790604697 81
1790604702 81
1790604707 81
1790604712 81
1790604717 81
1790604722 81
1790604727 81
1790604732 81
1790604737 81
1790604742 81
1790604747 81
1790604752 81
1790604757 81
1790604762 81
1790604767 81
1790604772 79
1790604777 79
1790604782 79
1790604787 79
```
</details>

---

