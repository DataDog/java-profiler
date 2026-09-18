---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 04:34:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 320 |
| Sample Rate | 5.33/sec |
| Health Score | 333% |
| Threads | 9 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 802 |
| Sample Rate | 13.37/sec |
| Health Score | 836% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 27-44 cores)</summary>

```
1789719885 27
1789719890 27
1789719895 44
1789719900 44
1789719905 44
1789719910 44
1789719915 44
1789719920 44
1789719925 44
1789719930 44
1789719935 44
1789719940 44
1789719945 44
1789719950 44
1789719955 44
1789719960 44
1789719965 44
1789719970 44
1789719975 44
1789719980 44
```
</details>

---

