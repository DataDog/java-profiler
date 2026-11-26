---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 08:19:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795698880 33
1795698885 33
1795698890 33
1795698895 33
1795698900 33
1795698905 33
1795698910 33
1795698915 33
1795698920 33
1795698925 28
1795698930 28
1795698935 28
1795698940 28
1795698945 28
1795698950 28
1795698955 28
1795698960 28
1795698965 28
1795698970 28
1795698975 28
```
</details>

---

