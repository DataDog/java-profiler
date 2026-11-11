---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 20:36:48 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 8 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (4 unique values: 74-94 cores)</summary>

```
1794360743 94
1794360748 94
1794360753 92
1794360758 92
1794360763 92
1794360768 92
1794360773 92
1794360778 92
1794360783 80
1794360788 80
1794360793 80
1794360799 80
1794360804 80
1794360809 80
1794360814 80
1794360819 80
1794360824 74
1794360829 74
1794360834 74
1794360839 74
```
</details>

---

