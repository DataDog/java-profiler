---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 06:16:19 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1795691194 74
1795691199 74
1795691204 74
1795691209 74
1795691214 74
1795691219 74
1795691224 74
1795691229 74
1795691234 74
1795691239 74
1795691244 74
1795691249 74
1795691254 74
1795691259 74
1795691264 74
1795691269 74
1795691274 76
1795691279 76
1795691284 76
1795691289 76
```
</details>

---

