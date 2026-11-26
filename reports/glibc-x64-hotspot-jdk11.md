---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:15:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 139 |
| Sample Rate | 2.32/sec |
| Health Score | 145% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 49-59 cores)</summary>

```
1795691118 49
1795691123 57
1795691128 57
1795691133 57
1795691138 57
1795691143 57
1795691148 57
1795691153 57
1795691158 57
1795691163 59
1795691168 59
1795691173 59
1795691178 59
1795691183 59
1795691188 59
1795691193 59
1795691198 59
1795691203 59
1795691208 59
1795691213 59
```
</details>

---

