---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-19 18:19:19 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 9 |
| Allocations | 581 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792448054 30
1792448059 30
1792448064 32
1792448069 32
1792448074 32
1792448079 32
1792448084 32
1792448089 32
1792448094 32
1792448099 32
1792448104 32
1792448109 32
1792448114 32
1792448119 32
1792448124 32
1792448129 32
1792448134 32
1792448139 32
1792448144 32
1792448149 32
```
</details>

---

