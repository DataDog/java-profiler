---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-21 10:05:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 278 |
| Sample Rate | 4.63/sec |
| Health Score | 289% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 30-37 cores)</summary>

```
1792591230 37
1792591235 37
1792591240 37
1792591245 37
1792591250 37
1792591255 37
1792591260 37
1792591265 37
1792591270 37
1792591275 37
1792591280 37
1792591285 37
1792591290 37
1792591295 37
1792591300 37
1792591305 37
1792591310 37
1792591315 37
1792591320 37
1792591325 30
```
</details>

---

