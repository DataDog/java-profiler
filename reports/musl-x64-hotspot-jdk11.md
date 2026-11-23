---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 12:00:54 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 838 |
| Sample Rate | 13.97/sec |
| Health Score | 873% |
| Threads | 10 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (2 unique values: 83-85 cores)</summary>

```
1795452901 83
1795452906 83
1795452911 83
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
1795452986 85
1795452991 85
1795452996 85
```
</details>

---

