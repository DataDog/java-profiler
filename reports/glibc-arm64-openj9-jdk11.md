---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 05:51:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 931 |
| Sample Rate | 15.52/sec |
| Health Score | 970% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 28-44 cores)</summary>

```
1795517184 44
1795517189 44
1795517194 44
1795517199 44
1795517204 44
1795517209 44
1795517214 44
1795517219 44
1795517224 44
1795517229 44
1795517234 44
1795517239 44
1795517244 44
1795517249 44
1795517254 44
1795517259 44
1795517264 44
1795517269 44
1795517275 44
1795517280 28
```
</details>

---

