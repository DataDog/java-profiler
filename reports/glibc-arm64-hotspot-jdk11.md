---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 09:34:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 47-59 cores)</summary>

```
1794580090 47
1794580095 47
1794580100 47
1794580105 47
1794580110 47
1794580115 47
1794580120 47
1794580125 47
1794580130 47
1794580135 47
1794580140 47
1794580145 47
1794580150 47
1794580155 59
1794580160 59
1794580165 59
1794580170 59
1794580175 59
1794580180 59
1794580185 59
```
</details>

---

