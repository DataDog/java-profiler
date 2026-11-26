---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 08:19:31 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 9 |
| Allocations | 552 |

<details>
<summary>CPU Timeline (3 unique values: 68-78 cores)</summary>

```
1795698865 78
1795698870 78
1795698875 78
1795698880 78
1795698885 78
1795698890 78
1795698895 78
1795698900 78
1795698905 78
1795698910 78
1795698915 78
1795698920 78
1795698925 78
1795698930 78
1795698935 78
1795698940 76
1795698945 76
1795698950 76
1795698955 68
1795698960 68
```
</details>

---

