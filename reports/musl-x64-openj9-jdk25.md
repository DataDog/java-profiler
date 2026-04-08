---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-08 09:54:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1775656119 42
1775656124 42
1775656129 42
1775656134 46
1775656139 46
1775656144 46
1775656149 43
1775656154 43
1775656159 43
1775656164 43
1775656169 43
1775656174 43
1775656179 48
1775656184 48
1775656189 48
1775656194 48
1775656199 48
1775656204 48
1775656209 48
1775656214 48
```
</details>

---

