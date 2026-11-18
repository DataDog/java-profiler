---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:10:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 9 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 13 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (1 unique values: 51-51 cores)</summary>

```
1795010778 51
1795010783 51
1795010788 51
1795010793 51
1795010798 51
1795010803 51
1795010808 51
1795010813 51
1795010818 51
1795010823 51
1795010828 51
1795010833 51
1795010838 51
1795010843 51
1795010848 51
1795010853 51
1795010858 51
1795010863 51
1795010868 51
1795010873 51
```
</details>

---

