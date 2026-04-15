---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-15 11:14:28 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 9 |
| Allocations | 572 |

<details>
<summary>CPU Timeline (3 unique values: 36-46 cores)</summary>

```
1776265574 41
1776265579 41
1776265584 46
1776265589 46
1776265594 46
1776265599 46
1776265604 46
1776265609 41
1776265614 41
1776265619 41
1776265624 41
1776265629 41
1776265634 41
1776265639 41
1776265644 41
1776265649 41
1776265654 41
1776265659 41
1776265664 41
1776265669 41
```
</details>

---

