---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 06:17:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (3 unique values: 27-33 cores)</summary>

```
1795778011 27
1795778016 27
1795778021 27
1795778026 27
1795778031 33
1795778036 33
1795778041 33
1795778046 33
1795778051 33
1795778056 33
1795778061 33
1795778066 33
1795778071 33
1795778076 33
1795778081 31
1795778086 31
1795778091 31
1795778096 31
1795778101 31
1795778106 31
```
</details>

---

