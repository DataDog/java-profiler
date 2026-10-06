---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-06 05:37:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 946 |
| Sample Rate | 15.77/sec |
| Health Score | 986% |
| Threads | 10 |
| Allocations | 550 |

<details>
<summary>CPU Timeline (2 unique values: 24-32 cores)</summary>

```
1791279061 32
1791279066 32
1791279071 32
1791279076 32
1791279081 32
1791279086 32
1791279091 24
1791279096 24
1791279101 24
1791279106 24
1791279111 24
1791279116 24
1791279121 24
1791279126 24
1791279131 24
1791279136 24
1791279141 24
1791279146 24
1791279151 24
1791279156 24
```
</details>

---

