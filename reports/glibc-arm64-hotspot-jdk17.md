---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 07:35:19 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 10 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794832269 43
1794832274 43
1794832279 43
1794832284 43
1794832289 48
1794832294 48
1794832300 48
1794832305 48
1794832310 43
1794832315 43
1794832320 43
1794832325 43
1794832330 43
1794832335 43
1794832340 43
1794832345 43
1794832350 43
1794832355 43
1794832360 43
1794832365 43
```
</details>

---

