---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-07 01:04:07 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1791349028 48
1791349033 48
1791349038 48
1791349043 48
1791349048 38
1791349053 38
1791349058 38
1791349063 38
1791349068 38
1791349073 38
1791349078 38
1791349083 38
1791349088 38
1791349093 38
1791349098 38
1791349103 38
1791349108 43
1791349113 43
1791349118 43
1791349123 43
```
</details>

---

