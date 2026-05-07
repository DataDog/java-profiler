---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 06:49:53 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778150802 64
1778150807 64
1778150812 64
1778150817 64
1778150822 64
1778150827 64
1778150832 64
1778150837 64
1778150842 64
1778150847 64
1778150852 64
1778150857 64
1778150862 64
1778150867 64
1778150872 64
1778150877 64
1778150882 64
1778150887 64
1778150892 64
1778150897 64
```
</details>

---

