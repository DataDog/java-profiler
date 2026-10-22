---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-22 06:46:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 270 |
| Sample Rate | 4.50/sec |
| Health Score | 281% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 302 |
| Sample Rate | 5.03/sec |
| Health Score | 314% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 12-32 cores)</summary>

```
1792665776 12
1792665781 12
1792665786 12
1792665791 12
1792665796 12
1792665801 12
1792665806 32
1792665811 32
1792665816 32
1792665821 32
1792665826 15
1792665831 15
1792665837 15
1792665842 15
1792665847 15
1792665852 15
1792665857 15
1792665862 15
1792665867 15
1792665872 15
```
</details>

---

