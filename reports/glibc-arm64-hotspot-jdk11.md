---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 00:56:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 14 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1790052782 40
1790052787 40
1790052792 40
1790052797 40
1790052802 40
1790052807 40
1790052812 40
1790052817 40
1790052822 40
1790052827 40
1790052832 40
1790052837 40
1790052842 40
1790052847 40
1790052852 40
1790052857 40
1790052862 40
1790052867 40
1790052872 40
1790052877 40
```
</details>

---

