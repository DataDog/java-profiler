---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 06:15:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 11 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (4 unique values: 71-82 cores)</summary>

```
1795691137 82
1795691142 82
1795691147 82
1795691152 80
1795691157 80
1795691162 80
1795691167 80
1795691172 80
1795691177 80
1795691182 78
1795691187 78
1795691192 78
1795691197 78
1795691202 78
1795691207 78
1795691212 78
1795691217 71
1795691222 71
1795691227 71
1795691232 71
```
</details>

---

