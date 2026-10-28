---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 13:11:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 25-30 cores)</summary>

```
1793207223 28
1793207228 28
1793207233 28
1793207238 28
1793207243 30
1793207248 30
1793207253 27
1793207258 27
1793207263 27
1793207268 27
1793207273 27
1793207278 27
1793207283 27
1793207288 27
1793207293 27
1793207298 27
1793207303 27
1793207308 27
1793207313 27
1793207318 27
```
</details>

---

