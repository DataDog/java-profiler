---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 15:01:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 9 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1793822201 74
1793822206 74
1793822211 74
1793822216 74
1793822221 74
1793822226 74
1793822231 74
1793822236 74
1793822241 76
1793822246 76
1793822251 76
1793822256 76
1793822261 76
1793822266 76
1793822271 76
1793822276 76
1793822281 76
1793822286 76
1793822291 76
1793822296 76
```
</details>

---

