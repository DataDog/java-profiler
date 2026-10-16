---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-16 09:30:24 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 7 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 246 |
| Sample Rate | 4.10/sec |
| Health Score | 256% |
| Threads | 13 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (3 unique values: 40-51 cores)</summary>

```
1792157114 51
1792157119 51
1792157124 51
1792157129 51
1792157134 51
1792157139 51
1792157144 51
1792157149 51
1792157154 51
1792157159 43
1792157164 43
1792157169 43
1792157174 40
1792157179 40
1792157184 40
1792157189 40
1792157194 40
1792157199 40
1792157204 40
1792157209 40
```
</details>

---

