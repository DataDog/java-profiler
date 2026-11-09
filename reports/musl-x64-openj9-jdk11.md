---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 10:36:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 9 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1794238189 79
1794238194 79
1794238199 79
1794238204 79
1794238209 79
1794238214 79
1794238219 79
1794238224 81
1794238229 81
1794238234 81
1794238239 81
1794238244 79
1794238249 79
1794238254 79
1794238259 79
1794238264 79
1794238269 77
1794238274 77
1794238279 77
1794238284 77
```
</details>

---

