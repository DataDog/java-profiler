---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 09:46:48 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 10 |
| Allocations | 556 |

<details>
<summary>CPU Timeline (2 unique values: 68-70 cores)</summary>

```
1793194953 70
1793194958 70
1793194963 70
1793194968 70
1793194973 70
1793194978 70
1793194983 68
1793194988 68
1793194993 68
1793194998 68
1793195003 68
1793195008 68
1793195013 68
1793195018 68
1793195023 68
1793195028 68
1793195033 70
1793195038 70
1793195043 70
1793195048 70
```
</details>

---

