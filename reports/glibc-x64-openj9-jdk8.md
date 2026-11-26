---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-26 06:15:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 167 |
| Sample Rate | 2.78/sec |
| Health Score | 174% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 39 |
| Sample Rate | 0.65/sec |
| Health Score | 41% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 80-84 cores)</summary>

```
1795691117 81
1795691122 81
1795691127 84
1795691132 84
1795691137 84
1795691142 84
1795691147 84
1795691152 84
1795691157 84
1795691162 84
1795691167 82
1795691172 82
1795691177 82
1795691182 82
1795691187 82
1795691192 82
1795691197 82
1795691202 82
1795691207 82
1795691212 82
```
</details>

---

