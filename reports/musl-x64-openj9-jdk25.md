---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-10 06:54:29 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (6 unique values: 49-82 cores)</summary>

```
1775818127 49
1775818132 49
1775818137 49
1775818142 75
1775818147 75
1775818152 75
1775818157 75
1775818162 75
1775818167 75
1775818172 75
1775818177 75
1775818182 75
1775818187 75
1775818192 70
1775818197 70
1775818202 66
1775818207 66
1775818212 66
1775818217 70
1775818222 70
```
</details>

---

