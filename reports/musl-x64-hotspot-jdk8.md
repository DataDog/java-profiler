---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-22 13:10:14 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 161 |
| Sample Rate | 2.68/sec |
| Health Score | 168% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 236 |
| Sample Rate | 3.93/sec |
| Health Score | 246% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 10-27 cores)</summary>

```
1792688652 27
1792688657 27
1792688662 10
1792688667 10
1792688672 10
1792688677 10
1792688682 10
1792688687 10
1792688692 10
1792688697 10
1792688702 10
1792688707 10
1792688712 10
1792688717 10
1792688722 10
1792688727 10
1792688732 10
1792688737 10
1792688742 10
1792688747 10
```
</details>

---

