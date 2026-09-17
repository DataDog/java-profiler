---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-17 18:02:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 15 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 30-64 cores)</summary>

```
1789682109 30
1789682114 30
1789682119 64
1789682124 64
1789682129 64
1789682134 64
1789682139 64
1789682144 64
1789682149 64
1789682154 64
1789682159 64
1789682164 64
1789682169 64
1789682174 64
1789682179 64
1789682184 64
1789682189 64
1789682194 64
1789682199 64
1789682204 64
```
</details>

---

