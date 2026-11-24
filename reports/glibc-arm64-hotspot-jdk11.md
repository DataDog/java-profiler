---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 05:15:26 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1795515006 32
1795515011 32
1795515016 32
1795515021 32
1795515026 32
1795515031 32
1795515036 32
1795515041 32
1795515046 32
1795515051 32
1795515056 32
1795515061 32
1795515066 32
1795515071 32
1795515076 32
1795515081 32
1795515086 32
1795515091 32
1795515096 32
1795515101 32
```
</details>

---

