---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ❌ FAIL

**Date:** 2026-01-27 09:00:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 4.93/sec |
| Health Score | 308% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 22 |
| Sample Rate | 0.73/sec |
| Health Score | 46% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769514276 24
1769514281 24
1769514286 24
1769514291 24
1769514296 24
1769514301 24
1769514306 24
1769514311 24
1769514316 24
1769514321 24
1769514326 24
1769514331 24
1769514336 24
1769514341 24
1769514346 24
1769514351 24
1769514356 24
1769514361 24
1769514366 24
1769514371 24
```
</details>

---

