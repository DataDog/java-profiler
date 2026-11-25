---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:33:27 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 9 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 88-96 cores)</summary>

```
1795631271 94
1795631276 94
1795631281 96
1795631286 96
1795631291 96
1795631296 96
1795631301 96
1795631306 96
1795631311 96
1795631316 96
1795631321 96
1795631326 96
1795631331 96
1795631336 96
1795631341 96
1795631346 96
1795631351 96
1795631356 96
1795631361 94
1795631366 94
```
</details>

---

