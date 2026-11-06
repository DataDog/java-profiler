---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-06 09:29:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793975064 30
1793975069 30
1793975074 30
1793975079 30
1793975084 30
1793975089 30
1793975094 30
1793975099 30
1793975104 30
1793975109 30
1793975114 30
1793975119 30
1793975124 30
1793975129 30
1793975134 30
1793975139 30
1793975144 30
1793975149 30
1793975154 30
1793975159 30
```
</details>

---

