---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 00:56:48 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 280 |
| Sample Rate | 4.67/sec |
| Health Score | 292% |
| Threads | 12 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (2 unique values: 11-48 cores)</summary>

```
1790052777 11
1790052782 11
1790052787 11
1790052792 11
1790052797 11
1790052802 11
1790052807 11
1790052812 11
1790052817 11
1790052822 11
1790052827 11
1790052832 11
1790052837 11
1790052842 11
1790052847 11
1790052852 48
1790052857 48
1790052862 11
1790052867 11
1790052872 11
```
</details>

---

