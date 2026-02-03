---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 09:53:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 11 |
| Allocations | 474 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1094 |
| Sample Rate | 18.23/sec |
| Health Score | 1139% |
| Threads | 13 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 72-96 cores)</summary>

```
1770130067 72
1770130072 96
1770130077 96
1770130082 96
1770130087 96
1770130092 96
1770130097 96
1770130102 96
1770130107 96
1770130112 96
1770130117 96
1770130122 96
1770130127 96
1770130132 96
1770130137 96
1770130142 96
1770130147 96
1770130152 96
1770130157 96
1770130162 96
```
</details>

---

