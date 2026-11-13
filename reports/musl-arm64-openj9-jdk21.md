---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 10:19:17 EST

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
| CPU Cores (start) | 39 |
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
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 13 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 39-64 cores)</summary>

```
1794582875 39
1794582880 39
1794582885 39
1794582890 39
1794582895 51
1794582900 51
1794582905 51
1794582910 51
1794582915 51
1794582920 51
1794582925 51
1794582930 51
1794582935 51
1794582940 51
1794582945 51
1794582950 51
1794582955 51
1794582960 51
1794582965 51
1794582970 51
```
</details>

---

