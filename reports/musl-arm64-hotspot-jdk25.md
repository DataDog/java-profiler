---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:18:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 9 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795706008 28
1795706013 28
1795706018 28
1795706023 33
1795706028 33
1795706033 28
1795706038 28
1795706043 28
1795706048 28
1795706053 28
1795706058 28
1795706063 28
1795706068 28
1795706073 28
1795706078 28
1795706083 28
1795706088 28
1795706093 28
1795706098 33
1795706103 33
```
</details>

---

