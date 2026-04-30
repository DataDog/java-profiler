---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-30 10:12:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777558064 64
1777558069 64
1777558074 64
1777558079 64
1777558084 64
1777558089 64
1777558094 64
1777558099 64
1777558104 64
1777558109 64
1777558114 64
1777558119 64
1777558124 64
1777558129 64
1777558134 64
1777558139 64
1777558144 64
1777558149 64
1777558154 64
1777558159 64
```
</details>

---

