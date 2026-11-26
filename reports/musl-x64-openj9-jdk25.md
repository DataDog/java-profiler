---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 06:09:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1795691102 32
1795691107 32
1795691112 32
1795691117 32
1795691122 32
1795691127 32
1795691132 32
1795691137 32
1795691142 32
1795691147 32
1795691152 32
1795691157 32
1795691162 32
1795691167 32
1795691172 32
1795691177 32
1795691182 32
1795691187 32
1795691192 32
1795691197 32
```
</details>

---

