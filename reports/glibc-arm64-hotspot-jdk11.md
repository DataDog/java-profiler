---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-23 05:47:30 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1787478225 59
1787478230 59
1787478235 59
1787478240 59
1787478245 64
1787478250 64
1787478255 64
1787478260 64
1787478265 64
1787478270 64
1787478275 64
1787478280 64
1787478285 64
1787478290 64
1787478295 64
1787478300 64
1787478305 64
1787478311 64
1787478316 64
1787478321 64
```
</details>

---

