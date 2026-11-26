---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:21:28 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 6 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (4 unique values: 54-60 cores)</summary>

```
1795706129 56
1795706134 56
1795706139 56
1795706144 54
1795706149 54
1795706154 54
1795706159 54
1795706164 54
1795706169 54
1795706174 54
1795706179 54
1795706184 54
1795706189 58
1795706194 58
1795706199 58
1795706204 58
1795706209 58
1795706214 58
1795706219 58
1795706224 58
```
</details>

---

