---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:33:27 EST

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
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1795631275 48
1795631280 48
1795631285 48
1795631290 48
1795631295 48
1795631300 48
1795631306 48
1795631311 48
1795631316 48
1795631321 48
1795631326 48
1795631331 48
1795631336 48
1795631341 48
1795631346 48
1795631351 48
1795631356 48
1795631361 48
1795631366 44
1795631371 44
```
</details>

---

