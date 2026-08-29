---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-29 00:58:55 EDT

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
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 11 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787979258 48
1787979263 48
1787979268 48
1787979273 48
1787979278 48
1787979283 48
1787979288 48
1787979293 48
1787979298 48
1787979303 48
1787979308 48
1787979313 48
1787979318 48
1787979323 43
1787979328 43
1787979333 43
1787979338 43
1787979343 43
1787979348 43
1787979353 43
```
</details>

---

