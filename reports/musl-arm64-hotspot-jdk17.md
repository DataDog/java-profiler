---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-23 21:25:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 7 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1787534360 46
1787534365 46
1787534370 43
1787534375 43
1787534380 43
1787534385 43
1787534390 43
1787534395 43
1787534400 43
1787534405 43
1787534410 43
1787534415 43
1787534420 43
1787534425 43
1787534430 43
1787534435 43
1787534440 48
1787534445 48
1787534450 48
1787534455 48
```
</details>

---

