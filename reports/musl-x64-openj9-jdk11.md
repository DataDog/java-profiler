---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 12:12:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 908 |
| Sample Rate | 15.13/sec |
| Health Score | 946% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (4 unique values: 69-75 cores)</summary>

```
1794589616 71
1794589621 71
1794589626 71
1794589631 71
1794589636 71
1794589641 71
1794589646 71
1794589651 71
1794589656 71
1794589661 71
1794589666 71
1794589671 71
1794589676 71
1794589681 71
1794589686 71
1794589691 69
1794589696 69
1794589701 69
1794589706 69
1794589711 71
```
</details>

---

