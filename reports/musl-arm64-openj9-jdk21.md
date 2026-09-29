---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 07:13:59 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 14 |
| Allocations | 114 |

<details>
<summary>CPU Timeline (3 unique values: 35-43 cores)</summary>

```
1790680134 38
1790680139 38
1790680144 38
1790680149 38
1790680154 38
1790680159 38
1790680164 38
1790680169 43
1790680174 43
1790680179 43
1790680184 43
1790680189 35
1790680194 35
1790680199 35
1790680204 35
1790680209 35
1790680214 35
1790680219 35
1790680224 35
1790680229 35
```
</details>

---

