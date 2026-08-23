---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-23 05:47:30 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 322 |
| Sample Rate | 5.37/sec |
| Health Score | 336% |
| Threads | 10 |
| Allocations | 159 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 11 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
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
1787478310 64
1787478315 64
1787478320 64
1787478325 64
1787478330 64
```
</details>

---

