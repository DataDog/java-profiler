---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-30 05:49:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1788083048 43
1788083053 43
1788083058 43
1788083063 43
1788083068 43
1788083073 43
1788083078 43
1788083083 43
1788083088 43
1788083093 43
1788083098 41
1788083103 41
1788083108 41
1788083113 41
1788083118 41
1788083123 41
1788083128 41
1788083133 41
1788083138 41
1788083143 41
```
</details>

---

