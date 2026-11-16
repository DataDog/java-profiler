---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-16 09:37:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 68-94 cores)</summary>

```
1794839609 78
1794839614 78
1794839619 78
1794839624 78
1794839629 78
1794839634 78
1794839639 78
1794839644 78
1794839649 94
1794839654 94
1794839659 82
1794839664 82
1794839669 82
1794839674 82
1794839680 82
1794839685 82
1794839690 82
1794839695 82
1794839700 82
1794839705 70
```
</details>

---

