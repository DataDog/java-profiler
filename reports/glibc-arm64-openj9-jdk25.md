---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 11:01:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 12 |
| Allocations | 122 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 12 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1794326139 42
1794326144 42
1794326149 42
1794326154 42
1794326159 42
1794326164 42
1794326169 42
1794326174 43
1794326179 43
1794326184 48
1794326189 48
1794326194 48
1794326199 48
1794326204 46
1794326209 46
1794326214 46
1794326219 46
1794326224 46
1794326229 46
1794326234 46
```
</details>

---

