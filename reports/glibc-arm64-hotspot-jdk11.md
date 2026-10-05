---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-05 11:49:01 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 9 |
| Allocations | 180 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (4 unique values: 44-51 cores)</summary>

```
1791215033 50
1791215038 50
1791215043 50
1791215048 50
1791215053 44
1791215058 44
1791215063 44
1791215068 44
1791215073 44
1791215078 44
1791215083 44
1791215088 44
1791215093 44
1791215098 44
1791215103 44
1791215108 44
1791215113 49
1791215118 49
1791215123 51
1791215128 51
```
</details>

---

