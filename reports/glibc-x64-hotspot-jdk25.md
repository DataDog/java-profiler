---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-12 10:27:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 10 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 12 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (2 unique values: 90-93 cores)</summary>

```
1773325278 90
1773325283 90
1773325289 90
1773325294 90
1773325299 90
1773325304 90
1773325309 90
1773325314 90
1773325319 93
1773325324 93
1773325329 93
1773325334 93
1773325339 93
1773325344 93
1773325349 93
1773325354 93
1773325359 93
1773325364 93
1773325369 93
1773325374 93
```
</details>

---

