---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ❌ FAIL

**Date:** 2026-01-27 09:00:57 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 10 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 5 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769514189 24
1769514194 24
1769514199 24
1769514204 24
1769514209 24
1769514214 24
1769514219 24
1769514224 24
1769514229 24
1769514234 24
1769514239 24
1769514244 24
1769514249 24
1769514254 24
1769514259 24
1769514264 24
1769514269 24
1769514274 24
1769514279 24
1769514284 24
```
</details>

---

