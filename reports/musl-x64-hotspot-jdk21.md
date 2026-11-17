---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 08:01:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1019 |
| Sample Rate | 16.98/sec |
| Health Score | 1061% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 87-89 cores)</summary>

```
1794920125 87
1794920130 87
1794920135 87
1794920140 87
1794920145 87
1794920151 87
1794920156 87
1794920161 87
1794920166 89
1794920171 89
1794920176 89
1794920181 89
1794920186 89
1794920191 87
1794920196 87
1794920201 87
1794920206 87
1794920211 87
1794920216 87
1794920221 87
```
</details>

---

