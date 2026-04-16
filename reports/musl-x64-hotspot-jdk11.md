---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-16 08:50:23 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1086 |
| Sample Rate | 18.10/sec |
| Health Score | 1131% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 76-81 cores)</summary>

```
1776343477 81
1776343482 81
1776343487 81
1776343492 81
1776343497 76
1776343502 76
1776343507 76
1776343512 76
1776343517 76
1776343522 76
1776343527 76
1776343532 76
1776343537 76
1776343542 76
1776343547 76
1776343552 76
1776343557 76
1776343562 76
1776343567 76
1776343572 76
```
</details>

---

