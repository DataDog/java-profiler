---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-11 06:35:24 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 302 |
| Sample Rate | 5.03/sec |
| Health Score | 314% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 34-51 cores)</summary>

```
1794396643 34
1794396648 34
1794396653 51
1794396658 51
1794396663 46
1794396669 46
1794396674 46
1794396679 46
1794396684 46
1794396689 46
1794396694 46
1794396699 46
1794396704 46
1794396709 46
1794396714 46
1794396719 46
1794396724 46
1794396729 46
1794396734 46
1794396739 46
```
</details>

---

