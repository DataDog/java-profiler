---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-25 16:28:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 14-18 cores)</summary>

```
1795641763 18
1795641768 18
1795641773 18
1795641778 18
1795641783 18
1795641788 18
1795641793 18
1795641798 18
1795641803 18
1795641808 18
1795641813 18
1795641818 18
1795641823 18
1795641828 18
1795641833 14
1795641838 14
1795641843 14
1795641848 14
1795641853 15
1795641858 15
```
</details>

---

