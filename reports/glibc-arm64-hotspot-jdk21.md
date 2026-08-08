---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-08 05:50:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 147 |
| Sample Rate | 2.45/sec |
| Health Score | 153% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1786182256 27
1786182261 27
1786182266 27
1786182271 32
1786182276 32
1786182281 32
1786182286 32
1786182291 32
1786182296 32
1786182301 32
1786182306 32
1786182311 32
1786182316 32
1786182321 32
1786182326 32
1786182331 32
1786182336 32
1786182341 32
1786182346 32
1786182351 32
```
</details>

---

