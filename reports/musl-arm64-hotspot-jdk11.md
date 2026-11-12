---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:35:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 134 |
| Sample Rate | 2.23/sec |
| Health Score | 139% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 6 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 39-51 cores)</summary>

```
1794508119 51
1794508124 51
1794508129 51
1794508134 51
1794508139 49
1794508144 49
1794508149 49
1794508154 49
1794508159 49
1794508164 49
1794508169 49
1794508174 49
1794508179 49
1794508184 51
1794508189 51
1794508194 51
1794508199 51
1794508204 51
1794508209 51
1794508214 39
```
</details>

---

