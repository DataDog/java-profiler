---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-24 15:44:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 68-79 cores)</summary>

```
1787600262 77
1787600267 77
1787600272 77
1787600277 79
1787600282 79
1787600287 79
1787600292 79
1787600297 79
1787600302 79
1787600307 79
1787600312 79
1787600317 74
1787600322 74
1787600327 74
1787600332 74
1787600337 74
1787600342 74
1787600347 74
1787600352 74
1787600357 68
```
</details>

---

