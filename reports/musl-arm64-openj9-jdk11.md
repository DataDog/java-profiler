---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 14:50:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 10 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 11 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 59-64 cores)</summary>

```
1795031119 59
1795031124 59
1795031129 59
1795031134 59
1795031139 59
1795031144 59
1795031149 59
1795031154 59
1795031159 59
1795031164 59
1795031169 59
1795031174 59
1795031179 59
1795031184 61
1795031189 61
1795031194 61
1795031199 61
1795031204 61
1795031209 64
1795031214 64
```
</details>

---

