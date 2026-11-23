---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:58:22 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (5 unique values: 55-66 cores)</summary>

```
1795452821 55
1795452826 55
1795452831 55
1795452836 55
1795452841 55
1795452846 55
1795452851 64
1795452856 64
1795452861 66
1795452866 66
1795452871 66
1795452876 59
1795452881 59
1795452886 59
1795452891 59
1795452896 59
1795452901 59
1795452906 59
1795452911 59
1795452916 59
```
</details>

---

