---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 04:49:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 13 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (5 unique values: 40-46 cores)</summary>

```
1792658568 45
1792658573 45
1792658578 45
1792658583 45
1792658588 45
1792658593 45
1792658598 45
1792658603 45
1792658608 45
1792658613 45
1792658618 43
1792658623 43
1792658628 43
1792658633 43
1792658638 46
1792658643 46
1792658648 41
1792658653 41
1792658658 41
1792658663 41
```
</details>

---

