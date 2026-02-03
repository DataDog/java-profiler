---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 09:53:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 10 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 13 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 56-86 cores)</summary>

```
1770130126 86
1770130131 86
1770130136 86
1770130141 56
1770130146 56
1770130151 56
1770130156 56
1770130161 56
1770130166 56
1770130171 56
1770130176 56
1770130181 56
1770130186 56
1770130191 56
1770130196 56
1770130201 56
1770130206 56
1770130211 56
1770130216 56
1770130221 60
```
</details>

---

