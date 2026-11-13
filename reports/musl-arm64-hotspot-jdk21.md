---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 13:36:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 11 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (4 unique values: 43-48 cores)</summary>

```
1794594662 44
1794594667 44
1794594672 44
1794594677 44
1794594682 44
1794594687 44
1794594692 44
1794594697 44
1794594702 46
1794594707 46
1794594712 46
1794594717 46
1794594722 46
1794594727 46
1794594732 46
1794594737 46
1794594742 46
1794594747 46
1794594752 48
1794594757 48
```
</details>

---

