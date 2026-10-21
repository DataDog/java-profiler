---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-21 06:49:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 10 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1199 |
| Sample Rate | 19.98/sec |
| Health Score | 1249% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1792579564 92
1792579569 92
1792579574 92
1792579579 92
1792579584 94
1792579589 94
1792579594 94
1792579599 92
1792579604 92
1792579609 92
1792579615 92
1792579620 92
1792579625 92
1792579630 90
1792579635 90
1792579640 90
1792579645 90
1792579650 90
1792579655 90
1792579660 90
```
</details>

---

