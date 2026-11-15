---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 16:13:22 EST

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 37-44 cores)</summary>

```
1794776930 37
1794776935 37
1794776940 37
1794776945 37
1794776950 37
1794776955 37
1794776960 37
1794776965 37
1794776970 37
1794776975 37
1794776980 37
1794776985 39
1794776990 39
1794776995 39
1794777000 39
1794777005 39
1794777010 39
1794777015 39
1794777020 39
1794777025 39
```
</details>

---

