---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 06:09:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 81-85 cores)</summary>

```
1795691097 85
1795691102 85
1795691107 85
1795691112 83
1795691117 83
1795691122 83
1795691127 83
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
```
</details>

---

