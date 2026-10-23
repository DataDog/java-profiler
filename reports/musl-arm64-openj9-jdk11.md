---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 10:56:48 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 11 |
| Allocations | 201 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 14 |
| Allocations | 158 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1792767114 46
1792767119 46
1792767124 46
1792767129 46
1792767134 46
1792767139 46
1792767144 46
1792767149 46
1792767154 46
1792767159 46
1792767164 46
1792767169 46
1792767174 46
1792767179 46
1792767184 46
1792767189 46
1792767194 41
1792767199 41
1792767204 41
1792767209 41
```
</details>

---

