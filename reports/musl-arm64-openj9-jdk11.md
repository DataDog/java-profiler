---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-22 16:32:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 173 |
| Sample Rate | 2.88/sec |
| Health Score | 180% |
| Threads | 11 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795382870 48
1795382875 48
1795382880 48
1795382885 48
1795382890 48
1795382895 48
1795382900 48
1795382905 48
1795382910 48
1795382915 48
1795382920 48
1795382925 48
1795382930 48
1795382935 43
1795382940 43
1795382945 43
1795382950 43
1795382955 43
1795382960 43
1795382965 43
```
</details>

---

