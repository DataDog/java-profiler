---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 09:38:16 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 12 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1793367226 34
1793367231 39
1793367236 39
1793367241 39
1793367246 39
1793367251 39
1793367256 39
1793367261 39
1793367266 39
1793367271 39
1793367276 39
1793367281 39
1793367286 39
1793367291 39
1793367296 39
1793367301 34
1793367306 34
1793367311 34
1793367316 34
1793367321 34
```
</details>

---

