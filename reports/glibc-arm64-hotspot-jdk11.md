---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 08:02:14 EST

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
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 7 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (8 unique values: 48-61 cores)</summary>

```
1795093102 48
1795093107 48
1795093112 48
1795093117 48
1795093122 50
1795093127 50
1795093132 48
1795093137 48
1795093142 48
1795093147 48
1795093152 48
1795093157 49
1795093162 49
1795093167 51
1795093172 51
1795093177 51
1795093182 51
1795093187 53
1795093192 53
1795093197 58
```
</details>

---

