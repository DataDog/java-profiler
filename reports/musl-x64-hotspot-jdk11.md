---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:15:16 EST

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
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 134 |
| Sample Rate | 2.23/sec |
| Health Score | 139% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 8 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (4 unique values: 82-85 cores)</summary>

```
1795691093 83
1795691098 83
1795691103 83
1795691108 83
1795691113 83
1795691118 83
1795691123 83
1795691128 83
1795691133 83
1795691138 83
1795691143 83
1795691148 83
1795691153 82
1795691158 82
1795691163 82
1795691168 82
1795691173 82
1795691178 82
1795691183 84
1795691188 84
```
</details>

---

