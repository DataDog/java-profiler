---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-13 06:34:59 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 10 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 50-56 cores)</summary>

```
1786617047 56
1786617052 56
1786617057 56
1786617062 56
1786617067 56
1786617072 56
1786617077 56
1786617082 50
1786617087 50
1786617092 50
1786617097 50
1786617102 50
1786617107 50
1786617112 50
1786617117 50
1786617122 50
1786617127 50
1786617132 50
1786617137 50
1786617142 50
```
</details>

---

