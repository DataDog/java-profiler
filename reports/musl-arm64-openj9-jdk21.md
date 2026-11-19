---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 02:47:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 173 |
| Sample Rate | 2.88/sec |
| Health Score | 180% |
| Threads | 11 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (3 unique values: 42-56 cores)</summary>

```
1795074193 56
1795074198 56
1795074203 56
1795074208 56
1795074213 56
1795074218 56
1795074223 56
1795074228 56
1795074233 56
1795074238 56
1795074243 56
1795074248 56
1795074253 43
1795074258 43
1795074263 43
1795074268 43
1795074273 43
1795074278 43
1795074283 43
1795074288 43
```
</details>

---

