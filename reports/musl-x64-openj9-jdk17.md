---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 11:32:49 EST

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
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795192079 85
1795192084 85
1795192089 85
1795192094 85
1795192099 85
1795192104 85
1795192109 85
1795192114 85
1795192119 85
1795192124 85
1795192129 85
1795192134 85
1795192139 85
1795192144 85
1795192149 85
1795192154 85
1795192159 87
1795192164 87
1795192169 87
1795192174 87
```
</details>

---

