---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-24 05:50:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 10 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787564721 43
1787564726 43
1787564731 43
1787564736 43
1787564741 43
1787564746 43
1787564751 43
1787564756 43
1787564761 43
1787564766 43
1787564771 43
1787564776 43
1787564781 43
1787564786 43
1787564791 43
1787564796 43
1787564801 43
1787564806 43
1787564811 48
1787564816 48
```
</details>

---

