---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-13 13:36:38 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 377 |
| Sample Rate | 6.28/sec |
| Health Score | 392% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794594662 32
1794594667 32
1794594672 32
1794594677 32
1794594682 32
1794594687 32
1794594692 32
1794594697 32
1794594702 30
1794594707 30
1794594712 30
1794594717 30
1794594722 30
1794594727 30
1794594732 30
1794594737 30
1794594742 30
1794594747 30
1794594752 30
1794594757 30
```
</details>

---

