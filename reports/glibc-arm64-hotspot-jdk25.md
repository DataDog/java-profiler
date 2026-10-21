---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-21 10:05:23 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 10 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1792591266 48
1792591271 48
1792591276 48
1792591281 48
1792591286 48
1792591291 48
1792591296 48
1792591301 48
1792591306 48
1792591311 48
1792591316 48
1792591321 48
1792591326 48
1792591331 48
1792591336 48
1792591341 48
1792591346 48
1792591351 48
1792591356 48
1792591361 48
```
</details>

---

