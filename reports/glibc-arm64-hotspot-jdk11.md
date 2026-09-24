---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 05:51:58 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 5 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1790243097 32
1790243102 32
1790243107 32
1790243112 32
1790243117 32
1790243122 32
1790243127 32
1790243132 32
1790243137 32
1790243142 32
1790243147 32
1790243152 32
1790243157 32
1790243162 32
1790243167 32
1790243172 32
1790243177 32
1790243182 32
1790243187 32
1790243192 32
```
</details>

---

