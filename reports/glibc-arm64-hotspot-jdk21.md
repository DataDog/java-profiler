---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-24 15:44:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 9 |
| Allocations | 105 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (5 unique values: 31-48 cores)</summary>

```
1787600206 48
1787600211 48
1787600216 48
1787600221 48
1787600226 48
1787600231 43
1787600236 43
1787600241 43
1787600246 43
1787600251 43
1787600256 36
1787600261 36
1787600266 31
1787600271 31
1787600276 31
1787600281 31
1787600286 36
1787600291 36
1787600296 36
1787600301 36
```
</details>

---

