---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 12:34:13 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 2.58/sec |
| Health Score | 161% |
| Threads | 11 |
| Allocations | 184 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 13 |
| Allocations | 112 |

<details>
<summary>CPU Timeline (3 unique values: 40-46 cores)</summary>

```
1794850187 40
1794850192 40
1794850197 40
1794850202 40
1794850207 40
1794850212 40
1794850217 40
1794850222 40
1794850227 40
1794850232 43
1794850237 43
1794850242 43
1794850247 43
1794850252 46
1794850257 46
1794850262 46
1794850267 46
1794850272 46
1794850277 46
1794850282 46
```
</details>

---

