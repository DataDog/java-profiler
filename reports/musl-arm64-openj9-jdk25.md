---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 06:16:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 905 |
| Sample Rate | 15.08/sec |
| Health Score | 942% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 32-52 cores)</summary>

```
1795432104 52
1795432109 52
1795432114 52
1795432119 52
1795432124 52
1795432129 52
1795432134 52
1795432139 52
1795432144 52
1795432149 52
1795432154 52
1795432159 52
1795432164 52
1795432169 52
1795432174 52
1795432179 52
1795432184 52
1795432189 52
1795432194 32
1795432199 32
```
</details>

---

