---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 11:54:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1795711819 45
1795711824 45
1795711829 45
1795711834 45
1795711839 45
1795711844 45
1795711849 48
1795711854 48
1795711859 48
1795711864 48
1795711869 48
1795711874 48
1795711879 48
1795711884 48
1795711889 48
1795711894 48
1795711899 48
1795711904 48
1795711909 48
1795711914 48
```
</details>

---

