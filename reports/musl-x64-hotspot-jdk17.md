---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-22 15:41:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 889 |
| Sample Rate | 14.82/sec |
| Health Score | 926% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 57-59 cores)</summary>

```
1795379786 59
1795379791 59
1795379796 59
1795379801 59
1795379806 59
1795379811 59
1795379816 59
1795379821 59
1795379826 59
1795379831 59
1795379836 57
1795379841 57
1795379846 57
1795379851 57
1795379856 57
1795379861 57
1795379866 57
1795379871 57
1795379876 57
1795379881 57
```
</details>

---

