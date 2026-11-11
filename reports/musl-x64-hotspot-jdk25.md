---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 20:36:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794360754 30
1794360759 30
1794360764 30
1794360769 30
1794360774 30
1794360779 30
1794360784 30
1794360789 30
1794360794 30
1794360799 30
1794360804 30
1794360809 32
1794360814 32
1794360819 32
1794360824 30
1794360829 30
1794360834 30
1794360839 30
1794360844 30
1794360849 30
```
</details>

---

