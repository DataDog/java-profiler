---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 06:15:17 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 10 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 42-59 cores)</summary>

```
1795691111 42
1795691116 42
1795691121 59
1795691126 59
1795691131 59
1795691137 59
1795691142 59
1795691147 59
1795691152 59
1795691157 59
1795691162 59
1795691167 59
1795691172 59
1795691177 59
1795691182 59
1795691187 59
1795691192 59
1795691197 59
1795691202 59
1795691207 59
```
</details>

---

