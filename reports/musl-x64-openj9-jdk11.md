---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 19:36:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 868 |
| Sample Rate | 14.47/sec |
| Health Score | 904% |
| Threads | 11 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (3 unique values: 74-79 cores)</summary>

```
1794357152 76
1794357157 76
1794357162 76
1794357167 76
1794357172 76
1794357177 76
1794357182 76
1794357187 76
1794357192 79
1794357197 79
1794357202 76
1794357207 76
1794357212 76
1794357217 76
1794357222 76
1794357227 76
1794357232 76
1794357237 74
1794357242 74
1794357247 74
```
</details>

---

