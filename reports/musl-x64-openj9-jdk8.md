---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-20 10:11:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 236 |
| Sample Rate | 3.93/sec |
| Health Score | 246% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 83-89 cores)</summary>

```
1792505114 83
1792505119 83
1792505124 83
1792505129 83
1792505134 83
1792505139 85
1792505144 85
1792505149 85
1792505154 85
1792505159 85
1792505164 83
1792505169 83
1792505174 83
1792505179 83
1792505184 83
1792505189 83
1792505194 83
1792505199 87
1792505204 87
1792505209 89
```
</details>

---

