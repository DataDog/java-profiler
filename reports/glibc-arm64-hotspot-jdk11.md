---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 08:54:43 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 38-46 cores)</summary>

```
1793800163 38
1793800168 38
1793800173 38
1793800178 38
1793800183 38
1793800188 38
1793800193 38
1793800198 38
1793800203 38
1793800208 38
1793800213 43
1793800218 43
1793800223 43
1793800228 43
1793800233 43
1793800238 43
1793800243 43
1793800248 43
1793800253 43
1793800258 43
```
</details>

---

