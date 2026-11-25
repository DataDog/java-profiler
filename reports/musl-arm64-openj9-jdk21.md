---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 11:43:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 262 |
| Sample Rate | 4.37/sec |
| Health Score | 273% |
| Threads | 12 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 30-35 cores)</summary>

```
1795624651 30
1795624656 30
1795624661 30
1795624666 30
1795624671 30
1795624676 30
1795624681 30
1795624686 30
1795624691 30
1795624696 30
1795624701 30
1795624706 30
1795624711 30
1795624716 35
1795624721 35
1795624726 35
1795624731 35
1795624736 35
1795624741 35
1795624746 35
```
</details>

---

