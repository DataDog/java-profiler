---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 12:00:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 467 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 68-75 cores)</summary>

```
1795452911 69
1795452916 69
1795452921 69
1795452926 69
1795452931 69
1795452936 68
1795452941 68
1795452946 68
1795452951 68
1795452956 68
1795452961 68
1795452966 68
1795452971 68
1795452976 68
1795452981 68
1795452986 68
1795452991 71
1795452996 71
1795453001 71
1795453006 71
```
</details>

---

