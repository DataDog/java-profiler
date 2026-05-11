---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-11 12:20:45 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (5 unique values: 75-82 cores)</summary>

```
1778516161 75
1778516166 75
1778516171 75
1778516176 75
1778516181 77
1778516186 77
1778516191 77
1778516196 82
1778516201 82
1778516206 82
1778516211 82
1778516216 82
1778516221 82
1778516226 82
1778516231 78
1778516236 78
1778516241 78
1778516246 78
1778516251 78
1778516256 78
```
</details>

---

