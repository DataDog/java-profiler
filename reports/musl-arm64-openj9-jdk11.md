---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 12:00:53 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 11 |
| Allocations | 150 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 11 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795452911 49
1795452916 49
1795452921 49
1795452926 49
1795452931 49
1795452936 49
1795452941 49
1795452946 49
1795452951 49
1795452956 49
1795452961 49
1795452966 49
1795452971 49
1795452976 49
1795452982 49
1795452987 49
1795452992 44
1795452997 44
1795453002 44
1795453007 44
```
</details>

---

