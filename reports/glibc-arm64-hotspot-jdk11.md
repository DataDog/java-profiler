---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 00:57:35 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 12 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1789966337 43
1789966342 43
1789966347 43
1789966352 43
1789966357 43
1789966362 43
1789966367 43
1789966372 43
1789966377 43
1789966382 43
1789966387 43
1789966392 43
1789966397 43
1789966402 43
1789966407 43
1789966412 43
1789966417 38
1789966422 38
1789966427 38
1789966432 38
```
</details>

---

