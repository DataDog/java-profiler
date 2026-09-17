---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 19:11:33 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 67-73 cores)</summary>

```
1789686408 67
1789686413 67
1789686418 67
1789686423 69
1789686428 69
1789686433 69
1789686438 69
1789686443 71
1789686448 71
1789686453 71
1789686458 71
1789686463 71
1789686468 71
1789686473 71
1789686478 67
1789686483 67
1789686488 67
1789686493 67
1789686498 71
1789686503 71
```
</details>

---

