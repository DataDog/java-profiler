---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-26 00:55:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1792990171 32
1792990176 32
1792990181 32
1792990186 32
1792990191 32
1792990196 32
1792990201 32
1792990206 32
1792990211 32
1792990216 32
1792990221 32
1792990226 32
1792990231 32
1792990236 32
1792990241 32
1792990246 32
1792990251 32
1792990256 32
1792990261 32
1792990266 32
```
</details>

---

