---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 16:58:36 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (5 unique values: 84-94 cores)</summary>

```
1790024054 85
1790024059 85
1790024064 85
1790024069 85
1790024074 86
1790024079 86
1790024084 86
1790024089 86
1790024094 86
1790024099 86
1790024104 86
1790024109 86
1790024114 86
1790024119 86
1790024124 86
1790024129 84
1790024134 84
1790024139 84
1790024144 84
1790024149 84
```
</details>

---

