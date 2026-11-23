---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ❌ FAIL

**Date:** 2026-11-23 12:00:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 83-85 cores)</summary>

```
1795452886 83
1795452891 83
1795452896 83
1795452901 83
1795452906 85
1795452911 85
1795452916 85
1795452921 85
1795452926 85
1795452931 85
1795452936 85
1795452941 85
1795452946 85
1795452951 85
1795452956 85
1795452961 85
1795452966 85
1795452971 85
1795452976 85
1795452981 85
```
</details>

---

