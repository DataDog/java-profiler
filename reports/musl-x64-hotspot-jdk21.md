---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ❌ FAIL

**Date:** 2026-11-13 13:36:38 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 940 |
| Sample Rate | 15.67/sec |
| Health Score | 979% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 85-88 cores)</summary>

```
1794594652 85
1794594657 85
1794594662 85
1794594667 85
1794594672 85
1794594677 85
1794594682 85
1794594687 85
1794594692 85
1794594697 85
1794594702 85
1794594707 85
1794594712 85
1794594717 85
1794594722 85
1794594727 85
1794594732 85
1794594737 88
1794594742 88
1794594747 88
```
</details>

---

