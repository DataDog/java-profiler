---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 13:08:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 8 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 33-40 cores)</summary>

```
1794506548 33
1794506553 33
1794506558 33
1794506563 33
1794506568 33
1794506573 33
1794506578 33
1794506583 35
1794506588 35
1794506593 35
1794506598 35
1794506603 35
1794506608 35
1794506613 35
1794506618 35
1794506623 35
1794506629 35
1794506634 35
1794506639 35
1794506644 35
```
</details>

---

