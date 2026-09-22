---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 00:56:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 10 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (3 unique values: 24-50 cores)</summary>

```
1790052752 27
1790052757 50
1790052762 50
1790052767 50
1790052772 24
1790052777 24
1790052782 24
1790052787 24
1790052792 24
1790052797 24
1790052802 24
1790052807 24
1790052812 24
1790052817 24
1790052822 24
1790052827 24
1790052832 24
1790052837 24
1790052842 24
1790052847 24
```
</details>

---

