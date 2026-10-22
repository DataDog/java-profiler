---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 19:41:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 24-32 cores)</summary>

```
1792712233 30
1792712238 30
1792712243 30
1792712248 30
1792712253 30
1792712258 30
1792712263 30
1792712268 30
1792712273 30
1792712278 30
1792712283 30
1792712288 30
1792712293 32
1792712298 32
1792712303 32
1792712308 32
1792712313 24
1792712318 24
1792712323 24
1792712328 24
```
</details>

---

