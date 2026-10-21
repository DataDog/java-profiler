---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 15:18:46 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 8 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 9 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 60-80 cores)</summary>

```
1792610074 80
1792610079 80
1792610084 78
1792610089 78
1792610094 78
1792610099 78
1792610104 78
1792610109 78
1792610114 78
1792610119 78
1792610124 78
1792610129 78
1792610134 80
1792610139 80
1792610144 80
1792610149 80
1792610154 80
1792610159 80
1792610164 60
1792610169 60
```
</details>

---

