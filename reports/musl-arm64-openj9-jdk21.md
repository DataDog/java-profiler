---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:58:21 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 264 |
| Sample Rate | 4.40/sec |
| Health Score | 275% |
| Threads | 13 |
| Allocations | 155 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795452816 64
1795452821 64
1795452826 64
1795452831 64
1795452836 64
1795452841 64
1795452846 64
1795452851 64
1795452856 64
1795452861 64
1795452866 64
1795452871 64
1795452876 64
1795452881 64
1795452886 64
1795452891 64
1795452896 64
1795452901 64
1795452906 64
1795452911 64
```
</details>

---

