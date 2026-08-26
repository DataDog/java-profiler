---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-26 14:48:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 95 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 12 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1787769783 48
1787769788 48
1787769793 48
1787769798 48
1787769803 48
1787769808 48
1787769813 48
1787769818 48
1787769823 48
1787769828 48
1787769833 44
1787769838 44
1787769843 44
1787769848 44
1787769853 44
1787769858 44
1787769863 44
1787769868 44
1787769873 44
1787769878 44
```
</details>

---

