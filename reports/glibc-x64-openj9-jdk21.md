---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 06:15:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 9 |
| Allocations | 90 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 70-81 cores)</summary>

```
1795691132 81
1795691137 81
1795691142 81
1795691147 81
1795691152 81
1795691157 81
1795691162 81
1795691167 81
1795691172 81
1795691177 81
1795691182 81
1795691187 81
1795691192 81
1795691197 81
1795691202 81
1795691207 70
1795691212 70
1795691217 70
1795691222 70
1795691227 70
```
</details>

---

