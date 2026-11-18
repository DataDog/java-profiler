---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 06:29:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 9 |
| Allocations | 156 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 15 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 26-39 cores)</summary>

```
1795001087 26
1795001092 26
1795001097 26
1795001102 26
1795001107 26
1795001112 26
1795001117 26
1795001122 26
1795001127 39
1795001132 39
1795001137 39
1795001142 39
1795001147 39
1795001152 39
1795001157 39
1795001162 39
1795001167 39
1795001172 39
1795001177 39
1795001182 39
```
</details>

---

